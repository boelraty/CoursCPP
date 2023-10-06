//-------------------------------------------------------------------------------------------------------------------
/*!	\brief	Exemple8
*	\file	main.cpp
*///-----------------------------------------------------------------------------------------------------------------

/*---- ITK Includes ----*/
#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkBinaryBallStructuringElement.h>
#include <itkBinaryDilateImageFilter.h>
#include <itkBinaryErodeImageFilter.h>
#include <itkGrayscaleFillholeImageFilter.h>
#include <itkImageFileWriter.h>

/*---- STL Includes ----*/
#include <string>


int main(int p_argc, char* p_argv[])
{
	//Typedef to define a image type
	typedef itk::Image<unsigned char, 2> UCharImageType;

	//Create the reader to read an image
	itk::ImageFileReader<UCharImageType>::Pointer reader = itk::ImageFileReader<UCharImageType>::New();
	reader->SetFileName("C:/binaryimage.png");
	reader->Update();

	//Typedef to define a StructuringElement type
	typedef itk::BinaryBallStructuringElement <unsigned char, 2> StructuringElementType;

	StructuringElementType structuringElement;
	structuringElement.SetRadius(1);
	structuringElement.CreateStructuringElement();

	typedef itk::Image<unsigned char, 2> UCharImageType;
	//Typedef to define a DilateFilter type
	typedef itk::BinaryDilateImageFilter <	UCharImageType,
		UCharImageType,
		StructuringElementType> DilateFilterType;

	//Typedef to define a ErodeFilter type
	typedef itk::BinaryErodeImageFilter <	UCharImageType,
		UCharImageType,
		StructuringElementType> ErodeFilterType;

	ErodeFilterType::Pointer eroder = ErodeFilterType::New();
	eroder->SetKernel(structuringElement);
	eroder->SetInput(reader->GetOutput());
	eroder->SetErodeValue(255);
	eroder->Update();



	DilateFilterType::Pointer dilater = DilateFilterType::New();
	dilater->SetKernel(structuringElement);
	dilater->SetInput(eroder->GetOutput());
	dilater->SetDilateValue(255);
	dilater->Update();

	//Typedef to define a FillFilter Type
	typedef itk::GrayscaleFillholeImageFilter < UCharImageType, UCharImageType > FillFilterType;

	FillFilterType::Pointer filler = FillFilterType::New();
	filler->SetInput(dilater->GetOutput());
	filler->Update();

	//Write the binary image
	itk::ImageFileWriter<UCharImageType>::Pointer writer = itk::ImageFileWriter<UCharImageType>::New();
	writer->SetFileName("C:/resultImage.png");
	writer->SetInput(filler->GetOutput());
	writer->Update();

	return 0;
}
