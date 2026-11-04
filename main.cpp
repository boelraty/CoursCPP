//-------------------------------------------------------------------------------------------------------------------
/*!	\brief	Test App
*	\file	main.cpp
*///-----------------------------------------------------------------------------------------------------------------

/*---- ITK Includes ----*/
#include <itkImage.h>

#include <iostream>

/*---- VTK Includes ----*/
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>

int main(int p_argc, char* p_argv[])
{
	std::cout << "Starting test ..." << std::endl;
	
	// Definit une image 2D dont chaque pixel contient un entier signe de type short.
	using ImageType = itk::Image<short, 2>;
	// Cree l'objet image ; le buffer de pixels n'est pas encore alloue.
	ImageType::Pointer image = ImageType::New();

	// Fixe le premier indice de la region a (0, 0), sans definir l'origine physique.
	ImageType::IndexType start;
	start.Fill(0);

	// Fixe le nombre de pixels a 512 sur chacun des deux axes.
	ImageType::SizeType size;
	size.Fill(512);

	// La region associe l'indice de depart et la taille de l'image.
	ImageType::RegionType region;
	region.SetIndex(start);
	region.SetSize(size);
	image->SetRegions(region);

	// Le spacing est la distance physique entre deux pixels voisins.
	// Un champ de 270 mm sur 512 pixels donne 0.52734375 mm par pixel.
	ImageType::SpacingType spacing;
	spacing[0] = 270.0 / size[0];
	spacing[1] = 270.0 / size[1];
	image->SetSpacing(spacing);

	// Alloue le buffer en memoire, puis initialise tous les pixels a -850.
	image->Allocate();
	image->FillBuffer(-850);
	std::cout << "ITK OK" << std::endl;

	// Relit les dimensions et le spacing depuis l'image pour les afficher.
	const auto imageSize = image->GetLargestPossibleRegion().GetSize();
	const auto imageSpacing = image->GetSpacing();
	// GetPixel utilise un indice : start designe ici le premier pixel, en (0, 0).
	std::cout << "Premier voxel : " << image->GetPixel(start) << std::endl;
	std::cout << "Dimensions : " << imageSize[0] << " x " << imageSize[1]
	          << " pixels" << std::endl;
	std::cout << "Spacing : " << imageSpacing[0] << " x " << imageSpacing[1]
	          << " mm/pixel" << std::endl;

	return 0;
} 