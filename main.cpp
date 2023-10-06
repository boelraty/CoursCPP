//-------------------------------------------------------------------------------------------------------------------
/*!	\brief	Exemple5
*	\file	main.cpp
*///-----------------------------------------------------------------------------------------------------------------

/*---- ITK Includes ----*/
#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkGDCMImageIO.h>

/*---- STL Includes ----*/
#include <string>


int main(int p_argc, char* p_argv[])
{
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

	std::cout << "Dimensions:" << reader->GetOutput()->GetLargestPossibleRegion().GetSize()[0] << std::endl;
	std::cout << "Spacing:" << reader->GetOutput()->GetSpacing()[0] << std::endl;
	
	//Check information from the GDCM ImageIO
	char* patientName = new char[50];
	gdcmObject->GetPatientName(patientName);
	char* birthdate = new char[50];
	gdcmObject->GetPatientDOB(birthdate);

	std::string modality;
	gdcmObject->GetValueFromTag(std::string("0008|0060"), modality);
	std::string seriesDate;
	gdcmObject->GetValueFromTag(std::string("0008|0021"), seriesDate);


	std::cout << "Patient name:" << patientName << std::endl;
	std::cout << "Patient birthdate:" << birthdate << std::endl;
	std::cout << "Modality:" << modality << std::endl;
	std::cout << "SeriesDate:" << seriesDate << std::endl;

	delete [] patientName;

	//START EX6
	//Create filter to apply threshold on image
	//itk::BinaryThresholdImageFilter<ShortImageType, UCharImageType>::Pointer thresholder =
	//Use reader->GetOutput() as input of thresholder



	//Write the binary image
	itk::ImageFileWriter<UCharImageType>::Pointer writer = itk::ImageFileWriter<UCharImageType>::New();
	//Refer to ex 3 and use output of thresholder

	return 0;
}
