//-------------------------------------------------------------------------------------------------------------------
/*!	\brief	Exemple1
*	\file	main.cpp
*///-----------------------------------------------------------------------------------------------------------------

/*---- ITK Includes ----*/
#include <itkImage.h>
#include <itkImageRegionConstIterator.h>
#include <itkImageRegionIterator.h>

int main(int p_argc, char* p_argv[])
{
	
	//Typedef to define a image type
	typedef itk::Image<unsigned char, 2> UCharImageType;

	//Create image
	//itk::Image<unsigned char, 2>::Pointer image = itk::Image<unsigned char, 2>::New();
	UCharImageType::Pointer image = UCharImageType::New();

	//Define starting point (0, 0)
	UCharImageType::IndexType startIndex;
	startIndex[0] = 0;
	startIndex[1] = 0;

	//Define image size
	UCharImageType::SizeType size;
	size[0] = 512;
	size[1] = 512;

	//Define image region
	UCharImageType::RegionType region;
	region.SetSize(size);
	region.SetIndex(startIndex);

	//Set the region to the image
	image->SetRegions(region);

	//Set image origin (where it starts in a 2D/3D referentiel)
	UCharImageType::PointType origin;
	origin[0] = 0;
	origin[1] = 0;
	image->SetOrigin(origin);

	//Set image spacing
	UCharImageType::SpacingType spacing;
	spacing[0] = 0.5;
	spacing[1] = 0.5;
	image->SetSpacing(spacing);

	//Allocate the image in memory
	image->Allocate(0);

	//Check image
	std::cout << "Dimension X:" << image->GetLargestPossibleRegion().GetSize()[0] << std::endl;
	std::cout << "Dimension Y:" << image->GetLargestPossibleRegion().GetSize()[1] << std::endl;
	std::cout << "Spacing X:" << image->GetSpacing()[0] << std::endl;
	std::cout << "Spacing Y:" << image->GetSpacing()[1] << std::endl;
	
	//START EXERCICE 2

	//Create const iterator for the iteration on the entire image
	itk::ImageRegionConstIterator<UCharImageType> toto
			(image, image->GetLargestPossibleRegion());

	//Initialize iterator to beginning
	toto.GoToBegin();

	//Iterate over the entire image to count the number of pixels
	int nbPixels = 0;
	while (!toto.IsAtEnd()) //Iterator IsAtEnd()
	{
		//Increment number of pixels
		++nbPixels;
		//Increment iterator
		++toto;
	}

	std::cout << "Number of pixels (512, 512) =" << nbPixels << std::endl;

	//Create a region for iterate over a part of the image
	UCharImageType::RegionType regionForIteration;

	//Define starting pixel for iteration
	UCharImageType::IndexType startingPixel;
	startingPixel[0] = 50;
	startingPixel[1] = 100;

	//Define size of region for iteration
	UCharImageType::SizeType regionSize;
	regionSize[0] = 100;
	regionSize[1] = 200;

	regionForIteration.SetSize(regionSize);
	regionForIteration.SetIndex(startingPixel);

	//Create non const iterator to fill the image with the rectangle
	itk::ImageRegionIterator<UCharImageType> iterator(image, regionForIteration);
	iterator.GoToBegin();
	nbPixels = 0;

	while (!iterator.IsAtEnd())
	{
		//Set a value to the pixel - Method Set
		iterator.Set(static_cast<unsigned char>(255));
		//Increment number of set pixels
		++nbPixels;

		//Increment iterator
		++iterator;
	}

	std::cout << "Number of pixels set:" << nbPixels << std::endl;

	//Access to a specific pixel - GetPixel(index)
	UCharImageType::IndexType pixel;
	pixel[0] = 60;
	pixel[1] = 150;
	std::cout << "Pixel (60, 150): " << int(image->GetPixel(pixel)) << std::endl;

	pixel[0] = 400;
	pixel[1] = 400;
	std::cout << "Pixel (400, 400): " << int(image->GetPixel(pixel)) << std::endl;

	return 0;
} 
