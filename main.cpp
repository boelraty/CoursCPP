//-------------------------------------------------------------------------------------------------------------------
/*!	\brief	Test App
*	\file	main.cpp
*///-----------------------------------------------------------------------------------------------------------------

/*---- ITK Includes ----*/
#include <itkBinaryThresholdImageFilter.h>
#include <itkGDCMImageIO.h>
#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkPNGImageIO.h>

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

int main(int p_argc, char* p_argv[])
{
	if (p_argc > 2)
	{
		std::cerr << "Usage : " << p_argv[0]
		          << " [dicom-file]" << std::endl;
		return EXIT_FAILURE;
	}

	// In a C++ string, ~ is not expanded to the home directory:
	// HOME is used to build the default path.
	std::string filename = "/home/vsimoes/Downloads/ImageDICOM";

	// Read a 2D slice with signed 16-bit intensities. Converting to uchar
	// before thresholding would lose intensity values.
	using ImageType = itk::Image<short, 2>;
	// The binary mask only uses 0 and 255: uchar is sufficient for the PNG.
	using BinaryImageType = itk::Image<unsigned char, 2>;
	using ReaderType = itk::ImageFileReader<ImageType>;
	using ThresholdType = itk::BinaryThresholdImageFilter<ImageType, BinaryImageType>;
	using WriterType = itk::ImageFileWriter<BinaryImageType>;
	// GDCM decodes the DICOM and its metadata, applying rescale parameters
	// when present: thresholding operates on the resulting pixel values.
	auto dicomIO = itk::GDCMImageIO::New();
	auto reader = ReaderType::New();
	reader->SetImageIO(dicomIO);
	reader->SetFileName(filename);

	try
	{
		// ITK processes data on demand: Update triggers the actual reading
		// of metadata and pixels here.
		reader->Update();
	}
	catch (const itk::ExceptionObject& error)
	{
		std::cerr << "Failed to read DICOM: " << error << std::endl;
		return EXIT_FAILURE;
	}

	const auto image = reader->GetOutput();
	// Size counts pixels; spacing is the physical distance between them in mm.
	// Origin is the physical position of pixel index (0, 0) in the 2D image.
	const auto imageSize = image->GetLargestPossibleRegion().GetSize();
	const auto imageSpacing = image->GetSpacing();
	const auto imageOrigin = image->GetOrigin();
	std::cout << std::setprecision(10);
	std::cout << "Dimensions : " << imageSize[0] << " x " << imageSize[1]
	          << " pixels" << std::endl;
	std::cout << "Spacing : " << imageSpacing[0] << " x " << imageSpacing[1]
	          << " mm" << std::endl;
	std::cout << "Origin : " << imageOrigin << " mm" << std::endl;

	// DICOM tags are identified by group|element in hexadecimal.
	// Missing or empty values are reported without inventing a default value.
	const auto printTag = [&dicomIO](const char* tag, const char* label)
	{
		std::string value;
		std::cout << label << " (" << tag << ") : ";
		if (dicomIO->GetValueFromTag(tag, value) &&
		    value.find_first_not_of(" \t\r\n") != std::string::npos)
		{
			std::cout << value;
		}
		else
		{
			std::cout << "[missing or empty]";
		}
		std::cout << std::endl;
	};

	std::cout << "\nDICOM tags:" << std::endl;
	printTag("0008|0060", "Modality");
	printTag("0010|0010", "Patient Name");
	printTag("0010|0030", "Patient Birth Date");
	printTag("0008|0022", "Acquisition Date (scan date)");
	printTag("0008|0020", "Study Date");
	printTag("0020|0032", "Image Position (Patient)");
	printTag("0028|0030", "Pixel Spacing (row, column)");
	printTag("0028|0010", "Rows");
	printTag("0028|0011", "Columns");

	// The physical field of view is size * spacing along the image axes.
	// Note: Pixel Spacing uses row/column order, unlike X/Y.
	std::cout << "\nPhysical field of view (X x Y): "
	          << imageSize[0] * imageSpacing[0] << " x "
	          << imageSize[1] * imageSpacing[1] << " mm" << std::endl;
	// Nominal slice thickness is not the spacing between slices;
	// a single image cannot provide that distance.
	printTag("0018|0050", "Slice Thickness (mm)");

	auto threshold = ThresholdType::New();
	threshold->SetInput(image);
	// Both filter bounds are inclusive: [150, maximum short value]
	// keeps values >= 150. Use a lower bound of 151 for strictly > 150.
	threshold->SetLowerThreshold(150);
	threshold->SetUpperThreshold(std::numeric_limits<ImageType::PixelType>::max());
	// Inside the interval: white (255). Outside: black (0).
	// The result is a mask, not a copy of the original intensities.
	threshold->SetInsideValue(255);
	threshold->SetOutsideValue(0);

	// The relative path places the PNG in the current working directory.
	// PNG does not preserve DICOM tags or the full patient-space geometry.
	const std::string outputFilename = "ImageDICOM-threshold150.png";
	auto writer = WriterType::New();
	writer->SetImageIO(itk::PNGImageIO::New());
	writer->SetFileName(outputFilename);
	// GetOutput connects the filter to the writer without computing the mask yet.
	writer->SetInput(threshold->GetOutput());
	try
	{
		// Update executes upstream thresholding, then writes the PNG to disk.
		writer->Update();
	}
	catch (const itk::ExceptionObject& error)
	{
		std::cerr << "Thresholding or PNG writing failed: " << error << std::endl;
		return EXIT_FAILURE;
	}
	std::cout << "\nBinary image (>= 150) saved: " << outputFilename << std::endl;

	return EXIT_SUCCESS;
}