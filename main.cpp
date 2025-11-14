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

	try
	{
		//#include <itkBinaryThresholdImageFilter.h>
		typedef itk::Image<unsigned char, 2> UCharImageType;
		typedef itk::BinaryThresholdImageFilter<ShortImageType, UCharImageType> Thresholder;

		//Create filter to apply threshold on image
		Thresholder::Pointer thresholder = Thresholder::New();
		thresholder->SetInput(reader->GetOutput());
		thresholder->SetLowerThreshold(160);
		thresholder->SetUpperThreshold(5000);
		thresholder->SetInsideValue(255);
		thresholder->SetOutsideValue(0);
		thresholder->Update();

		//Labelize the image
		typedef itk::Image<int, 2> IntImageType;
		typedef itk::ConnectedComponentImageFilter<UCharImageType, IntImageType> LabelerType;
		itk::ConnectedComponentImageFilter<UCharImageType, IntImageType>::Pointer labeler =
			itk::ConnectedComponentImageFilter<UCharImageType, IntImageType>::New();
		//Set input = outout of reader


		//Relabelize the image to get info about the group of found pixels
		typedef itk::RelabelComponentImageFilter<IntImageType, UCharImageType> RelabelerType;
		//    itk::RelabelComponentImageFilter<IntImageType, UCharImageType>::Pointer relabeler =


		//	std::cout << "Number of found objects :" << relabeler->GetNumberOfObjects() << std::endl;
		//	for (int i = 0 ; i < relabeler->GetNumberOfObjects() ; ++i)
		//		std::cout << "Area of objects " << i << ":" << relabeler->GetSizeOfObjectInPhysicalUnits(i) << std::endl;

			//Rescale the image to see colors on labelized output
		typedef itk::RescaleIntensityImageFilter<UCharImageType, UCharImageType> RescalerType;
		//    itk::RescaleIntensityImageFilter<UCharImageType, UCharImageType>::Pointer rescaler =
		//    ...

			//Write the binary image
		//  itk::ImageFileWriter<UCharImageType>::Pointer writer = itk::ImageFileWriter<UCharImageType>::New();
		//  //...


		//Write the binary image
		itk::ImageFileWriter<UCharImageType>::Pointer writer
			= itk::ImageFileWriter<UCharImageType>::New();
		writer->SetInput(thresholder->GetOutput());
		writer->SetFileName("image.png");
		writer->Write();

	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
	return 0;
}
