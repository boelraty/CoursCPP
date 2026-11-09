/*---- ITK Includes ----*/
#include <itkBinaryThresholdImageFilter.h>
#include <itkConnectedComponentImageFilter.h>
#include <itkGDCMImageIO.h>
#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkPNGImageIO.h>
#include <itkRelabelComponentImageFilter.h>
#include <itkRescaleIntensityImageFilter.h>

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>

int main()
{
	const std::string filename = "/home/vsimoes/Downloads/ImageDICOM";

	try
	{
		// Read one 2D DICOM slice using GDCM. Signed short preserves negative
		// intensities, which would be lost if the input were read as uchar.
		using ImageType = itk::Image<short, 2>;
		using ReaderType = itk::ImageFileReader<ImageType>;
		auto reader = ReaderType::New();
		reader->SetImageIO(itk::GDCMImageIO::New());
		reader->SetFileName(filename);
		reader->Update(); // Load the pixels and spacing before building the filters.

		// The threshold output is an 8-bit mask, not the original intensities:
		// selected pixels become 255 and all others become 0.
		using BinaryImageType = itk::Image<unsigned char, 2>;
		using ThresholdType = itk::BinaryThresholdImageFilter<ImageType, BinaryImageType>;
		auto threshold = ThresholdType::New();
		threshold->SetInput(reader->GetOutput());
		// Bounds are inclusive: pixels >= 150 become white.
		threshold->SetLowerThreshold(150);
		threshold->SetUpperThreshold(std::numeric_limits<ImageType::PixelType>::max());
		threshold->SetInsideValue(255);
		threshold->SetOutsideValue(0);

		// Use a wide label type so more than 255 objects can be identified.
		using LabelImageType = itk::Image<unsigned int, 2>;
		using ConnectedComponentType =
			itk::ConnectedComponentImageFilter<BinaryImageType, LabelImageType>;
		auto components = ConnectedComponentType::New();
		// Each connected group of nonzero pixels receives a distinct label.
		// Label 0 is background. Default 2D connectivity uses 4 neighbors,
		// so pixels touching only at a corner belong to different objects.
		components->SetInput(threshold->GetOutput());

		using RelabelType = itk::RelabelComponentImageFilter<LabelImageType, LabelImageType>;
		const double minimumArea = 50.0; // mm^2
		// Spacing is in mm: one pixel covers spacing X * spacing Y mm^2.
		const auto spacing = reader->GetOutput()->GetSpacing();
		const double pixelArea = spacing[0] * spacing[1];
		
		// Relabel expects a pixel count rather than a physical area.
		// Round up to keep only objects with an area >= minimumArea.
		const double minimumPixels = std::ceil(minimumArea / pixelArea);
		auto relabel = RelabelType::New();
		relabel->SetInput(components->GetOutput());
		// Small objects become background. By default, the remaining objects
		// are sorted by decreasing size and numbered consecutively from 1.
		relabel->SetMinimumObjectSize(
			static_cast<RelabelType::ObjectSizeType>(minimumPixels));
		relabel->Update(); // Execute labeling and filtering before querying sizes.

		// In 2D, physical sizes are areas computed from the image spacing.
		// Both vectors use the same order: index i describes label i + 1.
		// The background and discarded objects are not included.
		const auto& sizes = relabel->GetSizeOfObjectsInPhysicalUnits();
		const auto& pixelSizes = relabel->GetSizeOfObjectsInPixels();
		std::cout << "Number of objects: " << relabel->GetNumberOfObjects() << std::endl;
		for (std::size_t i = 0; i < sizes.size(); ++i)
		{
			std::cout << "Object " << i + 1 << ": " << sizes[i] << " mm^2 - "
			          << pixelSizes[i] << " pixels" << std::endl;
		}

		// Rescale is for display only: an 8-bit PNG cannot preserve more
		// than 255 distinct nonzero labels.
		// It maps the label range to [0, 255], without changing object areas.
		using RescaleType =
			itk::RescaleIntensityImageFilter<LabelImageType, BinaryImageType>;
		auto rescale = RescaleType::New();
		rescale->SetInput(relabel->GetOutput());
		rescale->SetOutputMinimum(0);
		rescale->SetOutputMaximum(255);

		const std::string outputFilename = "ImageDICOM-components.png";
		// Save only the final visualization in the current working directory.
		// PNG does not preserve the DICOM metadata or full patient geometry.
		using WriterType = itk::ImageFileWriter<BinaryImageType>;
		auto writer = WriterType::New();
		writer->SetImageIO(itk::PNGImageIO::New());
		writer->SetFileName(outputFilename);
		writer->SetInput(rescale->GetOutput());
		writer->Update(); // Execute rescaling, then write the PNG to disk.
		std::cout << "Final image saved: " << outputFilename << std::endl;
	}
	catch (const itk::ExceptionObject& error)
	{
		std::cerr << "Image processing or PNG writing failed: " << error << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
