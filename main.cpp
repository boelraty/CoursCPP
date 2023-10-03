//-------------------------------------------------------------------------------------------------------------------
/*!	\brief	Exemple1
*	\file	main.cpp
*///-----------------------------------------------------------------------------------------------------------------

/*---- ITK Includes ----*/
#include <itkImage.h>


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
	image->Allocate();

	//Check image
	std::cout << "Dimension X:" << image->GetLargestPossibleRegion().GetSize()[0] << std::endl;
	std::cout << "Dimension Y:" << image->GetLargestPossibleRegion().GetSize()[1] << std::endl;
	std::cout << "Spacing X:" << image->GetSpacing()[0] << std::endl;
	std::cout << "Spacing Y:" << image->GetSpacing()[1] << std::endl;
	
	return 0;
} 
