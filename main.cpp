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
	itk::GDCMImageIO::Pointer ioObject = itk::GDCMImageIO::New();

	//Create the reader to read an image
	itk::ImageFileReader<ShortImageType>::Pointer reader 
		= itk::ImageFileReader<ShortImageType>::New();
	reader->SetFileName("C:/Users/vsimoes/Downloads/ImageDICOM");
	reader->SetImageIO(ioObject);
	reader->Update();

	//Write dimensions and spacing
	std::cout << "Dimensions X :" << reader->GetOutput()->GetLargestPossibleRegion().GetSize()[0] << std::endl;
	std::cout << "Dimensions Y :" << reader->GetOutput()->GetLargestPossibleRegion().GetSize()[1] << std::endl;
	std::cout << "Spacing X :" << reader->GetOutput()->GetSpacing()[0] << std::endl;
	std::cout << "Spacing Y :" << reader->GetOutput()->GetSpacing()[1] << std::endl;

	//Check information from the GDCM ImageIO
	char* patientbirthdate = new char[20];
	char* patientid = new char[20];
	char* studydate = new char[20];
	std::string patientname;
	std::string modality;

	//Get DICOM data
	ioObject->GetValueFromTag("0010|0010", patientname);
	ioObject->GetPatientDOB(patientbirthdate);
	ioObject->GetPatientID(patientid);
	ioObject->GetStudyDate(studydate);
	ioObject->GetValueFromTag("0008|0060", modality);

	std::cout << "Patient name :" << patientname << std::endl;
	std::cout << "Patient DOB :" << patientbirthdate << std::endl;
	std::cout << "Patient ID :" << patientid << std::endl;
	std::cout << "Study Date :" << studydate << std::endl;

	std::cout << "Modality :" << modality.c_str() << std::endl;


	//Delete allocated pointers
	delete[] patientbirthdate;
	delete[] patientid;
	delete[] studydate;


	//Create filter to apply threshold on image
	//itk::BinaryThresholdImageFilter<ShortImageType, UCharImageType>::Pointer thresholder =
	//Use reader->GetOutput() as input of thresholder


	//Write the binary image
	itk::ImageFileWriter<UCharImageType>::Pointer writer = itk::ImageFileWriter<UCharImageType>::New();
	//Refer to ex 3 and use output of thresholder

	return 0;
}
