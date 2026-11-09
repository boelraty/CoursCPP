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
		using ImageType = itk::Image<short, 2>;
		using ReaderType = itk::ImageFileReader<ImageType>;
		auto reader = ReaderType::New();
		reader->SetImageIO(itk::GDCMImageIO::New());
		reader->SetFileName(filename);
		reader->Update();

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
		components->SetInput(threshold->GetOutput());

		using RelabelType = itk::RelabelComponentImageFilter<LabelImageType, LabelImageType>;
		const double minimumArea = 50.0; // mm^2
		const auto spacing = reader->GetOutput()->GetSpacing();
		const double pixelArea = spacing[0] * spacing[1];
		
		// Round up to keep only objects with an area >= minimumArea.
		const double minimumPixels = std::ceil(minimumArea / pixelArea);
		auto relabel = RelabelType::New();
		relabel->SetInput(components->GetOutput());
		relabel->SetMinimumObjectSize(
			static_cast<RelabelType::ObjectSizeType>(minimumPixels));
		relabel->Update();

		// In 2D, physical sizes are areas computed from the image spacing.
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
		using RescaleType =
			itk::RescaleIntensityImageFilter<LabelImageType, BinaryImageType>;
		auto rescale = RescaleType::New();
		rescale->SetInput(relabel->GetOutput());
		rescale->SetOutputMinimum(0);
		rescale->SetOutputMaximum(255);

		const std::string outputFilename = "ImageDICOM-components.png";
		using WriterType = itk::ImageFileWriter<BinaryImageType>;
		auto writer = WriterType::New();
		writer->SetImageIO(itk::PNGImageIO::New());
		writer->SetFileName(outputFilename);
		writer->SetInput(rescale->GetOutput());
		writer->Update();
		std::cout << "Final image saved: " << outputFilename << std::endl;
	}
	catch (const itk::ExceptionObject& error)
	{
		std::cerr << "Image processing or PNG writing failed: " << error << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
