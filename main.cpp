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

	//Create the GDCM image IO

	//Create the reader to read an image
	itk::ImageFileReader<ShortImageType>::Pointer reader = itk::ImageFileReader<ShortImageType>::New();


	//Write dimensions and spacing
	//std::cout << "Dimensions X :" << reader->GetOutput()->GetLargestPossibleRegion().GetSize()[0];


	//Check information from the GDCM ImageIO
	char* patientname = new char;
	char* patientbirthdate = new char;
	char* patientid = new char;
	char* studydate = new char;
	std::string modality;

	//Get DICOM data
	//gdcmImageIO->Get...

	std::cout << "Patient name :" << patientname << std::endl;
	//...
	std::cout << "Modality :" << modality.c_str() << std::endl;


	//Delete allocated pointers
	delete[] patientname;
	delete[] patientbirthdate;
	delete[] patientid;
	delete[] studydate;
	return 0;
}
