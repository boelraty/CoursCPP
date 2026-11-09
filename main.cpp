//-------------------------------------------------------------------------------------------------------------------
/*!	\brief	Test App
*	\file	main.cpp
*///-----------------------------------------------------------------------------------------------------------------

/*---- ITK Includes ----*/
#include <itkGDCMImageIO.h>
#include <itkGDCMSeriesFileNames.h>
#include <itkImage.h>
#include <itkImageSeriesReader.h>

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

int main(int p_argc, char* p_argv[])
{
	if (p_argc > 2)
	{
		std::cerr << "Usage : " << p_argv[0]
		          << " [dossier-dicom]" << std::endl;
		return EXIT_FAILURE;
	}

	// The shell does not expand ~ inside a C++ string.
	std::string directory;
	if (p_argc >= 2)
	{
		directory = p_argv[1];
	}
	else
	{
		const char* home = std::getenv("HOME");
		if (home == nullptr || home[0] == '\0')
		{
			std::cerr << "HOME non defini : fournir le chemin du dossier DICOM."
			          << std::endl;
			return EXIT_FAILURE;
		}
		directory = std::string(home) + "/Data/ShoulderCases/Patient521/DICOM/Raw2";
	}

	using ImageType = itk::Image<short, 3>;
	using ReaderType = itk::ImageSeriesReader<ImageType>;
	auto seriesNames = itk::GDCMSeriesFileNames::New();
	auto dicomIO = itk::GDCMImageIO::New();
	auto reader = ReaderType::New();
	reader->SetImageIO(dicomIO);

	try
	{
		seriesNames->SetDirectory(directory);
		const auto& seriesUIDs = seriesNames->GetSeriesUIDs();
		if (seriesUIDs.empty())
		{
			std::cerr << "Aucune serie DICOM trouvee dans : " << directory << std::endl;
			return EXIT_FAILURE;
		}

		if (seriesUIDs.size() > 1)
		{
			std::cerr << "Plusieurs series DICOM : fournir un dossier contenant une seule serie."
			          << std::endl;
			for (const auto& uid : seriesUIDs)
			{
				std::cerr << "  " << uid << std::endl;
			}
			return EXIT_FAILURE;
		}

		const auto& seriesUID = seriesUIDs.front();
		// GDCM sorts slices by their physical position, not by filename.
		const auto& filenames = seriesNames->GetFileNames(seriesUID);
		if (filenames.empty())
		{
			std::cerr << "Aucun fichier DICOM pour la serie : " << seriesUID << std::endl;
			return EXIT_FAILURE;
		}
		reader->SetFileNames(filenames);
		reader->Update();
		std::cout << "Serie DICOM : " << seriesUID << std::endl;
		std::cout << "Nombre de fichiers : " << filenames.size() << std::endl;
	}
	catch (const itk::ExceptionObject& error)
	{
		std::cerr << "Echec de la lecture DICOM : " << error << std::endl;
		return EXIT_FAILURE;
	}

	const auto image = reader->GetOutput();
	const auto imageSize = image->GetLargestPossibleRegion().GetSize();
	const auto imageSpacing = image->GetSpacing();
	const auto imageOrigin = image->GetOrigin();
	std::cout << std::setprecision(10);
	std::cout << "Dimensions : " << imageSize[0] << " x " << imageSize[1]
	          << " x " << imageSize[2] << " voxels" << std::endl;
	std::cout << "Spacing : " << imageSpacing[0] << " x " << imageSpacing[1]
	          << " x " << imageSpacing[2] << " mm" << std::endl;
	std::cout << "Origin : " << imageOrigin << " mm" << std::endl;

	// DICOM identifiers use the group|element format.
	// Missing or empty values are reported without inventing a default value.
	const auto printTag = [&dicomIO](const char* tag, const char* label)
	{
		std::string value;
		std::cout << label << " (" << tag << ") : ";
		if (dicomIO->GetValueFromTag(tag, value) &&
		    value.find_first_not_of(" \t\r\n") != std::string::npos)
		{
			std::cout << value;
		}
		else
		{
			std::cout << "[absent ou vide]";
		}
		std::cout << std::endl;
	};

	std::cout << "\nTags DICOM (derniere coupe lue) :" << std::endl;
	printTag("0008|0060", "Modality");
	printTag("0010|0010", "Patient Name");
	printTag("0010|0030", "Patient Birth Date");
	printTag("0008|0022", "Acquisition Date (date du scan)");
	printTag("0008|0020", "Study Date (date de l'etude)");
	printTag("0020|0032", "Image Position (Patient)");
	printTag("0028|0030", "Pixel Spacing (ligne, colonne)");
	printTag("0028|0010", "Rows");
	printTag("0028|0011", "Columns");

	// The physical field of view is size * spacing along the image axes.
	// The Pixel Spacing tag uses row/column order, unlike the X/Y axes.
	std::cout << "\nTaille physique du champ (X x Y) : "
	          << imageSize[0] * imageSpacing[0] << " x "
	          << imageSize[1] * imageSpacing[1] << " mm" << std::endl;
	if (imageSize[2] > 1)
	{
		std::cout << "Taille physique du champ en Z : "
		          << imageSize[2] * imageSpacing[2] << " mm" << std::endl;
	}
	else
	{
		// The Z spacing of a single slice does not guarantee its physical thickness.
		printTag("0018|0050", "Slice Thickness (mm)");
	}

	return EXIT_SUCCESS;
}