//-------------------------------------------------------------------------------------------------------------------
/*!	\brief	Exemple4
*	\file	main.cpp
*///-----------------------------------------------------------------------------------------------------------------

/*---- ITK Includes ----*/
#include <itkImage.h>
#include <itkImageRegionConstIterator.h>
#include <itkImageFileReader.h>

int main(int p_argc, char* p_argv[])
{
	//Typedef to define a image type
	typedef itk::Image<unsigned char, 2> UCharImageType;

	//Create the reader to read an image
	itk::ImageFileReader<UCharImageType>::Pointer reader = itk::ImageFileReader<UCharImageType>::New();
	reader->SetFileName("C:/test.png");
	reader->Update();

	//Write dimensions and spacing
	std::cout << "Dimensions X :" << reader->GetOutput()->GetLargestPossibleRegion().GetSize()[0] << std::endl;
	std::cout << "Dimensions Y :" << reader->GetOutput()->GetLargestPossibleRegion().GetSize()[1] << std::endl;
	std::cout << "Spacing X :" << reader->GetOutput()->GetSpacing()[0] << std::endl;
	std::cout << "Spacing Y :" << reader->GetOutput()->GetSpacing()[1] << std::endl;

	//Create an iterator to check if the image contains the rectangle
	itk::ImageRegionConstIterator<UCharImageType> iterator(reader->GetOutput(), reader->GetOutput()->GetLargestPossibleRegion());

	//Initialize iterator to begin (GoToBegin())
	iterator.GoToBegin();

	int nbPixels = 0;

	while (!iterator.IsAtEnd())
	{
		//Check if pixel = 255
		if (iterator.Get() == static_cast<unsigned char>(255))
			++nbPixels;

		//Increment iterator
		++iterator;
	}

	std::cout << "Nb pixels equal to 255 :" << nbPixels << std::endl;

	return 0;
}
