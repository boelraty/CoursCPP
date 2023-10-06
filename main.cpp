//-------------------------------------------------------------------------------------------------------------------
/*!	\brief	Exemple5
*	\file	main.cpp
*///-----------------------------------------------------------------------------------------------------------------

/*---- ITK Includes ----*/
#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkGDCMImageIO.h>
#include <itkBinaryThresholdImageFilter.h>

/*---- STL Includes ----*/
#include <string>


int main(int p_argc, char* p_argv[])
{
	try {
		//Typedef to define a image type (refer to exercice 1 and replace unsigned char with signed short)
		typedef itk::Image<short, 2> ShortImageType;

		//Create the GDCM image IO
		itk::GDCMImageIO::Pointer gdcmObject = itk::GDCMImageIO::New();

		//Create the reader to read an image
		itk::ImageFileReader<ShortImageType>::Pointer reader
			= itk::ImageFileReader<ShortImageType>::New();
		reader->SetFileName("C:/Users/vsimoes/Downloads/ImageDICOM");
		reader->SetImageIO(gdcmObject);
		reader->Update();
		
		//START EX6
		//Create filter to apply threshold on image
		typedef itk::Image<unsigned char, 2> UCharImageType;
		typedef itk::BinaryThresholdImageFilter<ShortImageType, UCharImageType> ThresholderType;
		ThresholderType::Pointer thresholder = ThresholderType::New();
		thresholder->SetInput(reader->GetOutput());
		thresholder->SetLowerThreshold(150);
		thresholder->SetUpperThreshold(3000);
		thresholder->SetInsideValue(255);
		thresholder->SetOutsideValue(0);
		thresholder->Update();

		//Write the binary image
		itk::ImageFileWriter<UCharImageType>::Pointer writer
			= itk::ImageFileWriter<UCharImageType>::New();
		writer->SetFileName("C:/image.png");
		writer->SetInput(thresholder->GetOutput());
		writer->Update();

	}
	catch (itk::ExceptionObject& ex)
	{
		std::cout << ex.what() << std::endl;
	}
	return 0;
}
