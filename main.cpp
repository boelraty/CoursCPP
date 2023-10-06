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
#include <itkConnectedComponentImageFilter.h>
#include <itkRelabelComponentImageFilter.h>
#include <itkRescaleIntensityImageFilter.h>

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

		//Start EX7

		//Labelize the image
		typedef itk::ConnectedComponentImageFilter<UCharImageType, ShortImageType> CCFilterType;
		CCFilterType::Pointer labeler = CCFilterType::New();
		labeler->SetInput(thresholder->GetOutput());
		labeler->Update();

		//Relabelize the image to get info about the group of found pixels
		typedef itk::RelabelComponentImageFilter<ShortImageType, UCharImageType> RelabelerType;
		RelabelerType::Pointer relabeler = RelabelerType::New();
		relabeler->SetInput(labeler->GetOutput());
		relabeler->SetMinimumObjectSize(100);
		relabeler->Update();

	std::cout << "Number of found objects :" << relabeler->GetNumberOfObjects() << std::endl;
	for (int i = 0 ; i < relabeler->GetNumberOfObjects() ; ++i)
		std::cout << "Area of objects " << i << ":" 
		<< relabeler->GetSizeOfObjectInPhysicalUnits(i) << std::endl;


	//Rescale the image to see colors on labelized output
	typedef itk::RescaleIntensityImageFilter<UCharImageType, UCharImageType> RescalerType;
	RescalerType::Pointer rescaler = RescalerType::New();
	rescaler->SetInput(relabeler->GetOutput());
	rescaler->Update();

	itk::ImageFileWriter<UCharImageType>::Pointer writer2 =
		itk::ImageFileWriter<UCharImageType>::New();
	writer2->SetInput(rescaler->GetOutput());
	writer2->SetFileName("C:/rescale.png");
	writer2->Update();


	//Write the binary image
//  itk::ImageFileWriter<UCharImageType>::Pointer writer = itk::ImageFileWriter<UCharImageType>::New();
//  //...

	}
	catch (itk::ExceptionObject& ex)
	{
		std::cout << ex.what() << std::endl;
	}
	return 0;
}
