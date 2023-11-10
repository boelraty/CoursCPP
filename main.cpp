//-------------------------------------------------------------------------------------------------------------------
/*!	\brief	Exemple12
*	\file	main.cpp
*///-----------------------------------------------------------------------------------------------------------------

/*---- STD Includes ----*/
#include <filesystem>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>

/*---- ITK Includes ----*/
#include <itkImage.h>

/*---- VTK Includes ----*/
#include <vtkImageData.h>
#include <vtkImageFlip.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkShortArray.h>
#include <vtkSmartPointer.h>

//Define image types
typedef itk::Image<signed short, 2> ShortImageType;

struct Dimensions
{
	int x = 0;
	int y = 0;
	int z = 0;
};

struct Spacing
{
	double x = 0.;
	double y = 0.;
	double z = 0.;
};

//Method to segment a vtkImageData
vtkPolyData* segmentData(const std::vector<ShortImageType::Pointer>& p_inputImages,
	const int p_lowerThreshold,
	const int p_upperThreshold,
	const Dimensions p_dimensions,
	const Spacing p_spacing)
{
	
	//Apply threshold on each raw images - ITK Ex6
	//Same as ITKReader with itk::BinaryThresholdImageFilter
	for (int z = 0; z < p_inputImages.size(); ++z)
	{
		//Create thresholder and save outpout in a list if images

	}

	//Build Image Data for input of marching cubes - VTK Ex12 and prior exemples with raw images

	//Apply the marching cubes - VTK Ex12

	//Return resulting mesh
	vtkPolyData* mesh = vtkPolyData::New();
	//mesh->DeepCopy(marchingcubes->GetOutput());

	return mesh;
}


int main(int p_argc, char* p_argv[])
{
	//Define input path
	const std::string inputPath = "C:/Users/vsimoes/ownCloud/CoursISEN/Data/Patient521/Patient521/Segmented";

	//Search all files in the directory
	std::vector<std::string> listOfFiles;
	for (const auto& file : std::filesystem::directory_iterator{ inputPath })
		listOfFiles.push_back(file.path().string());

	std::cout << "Number of files found: " << listOfFiles.size() << std::endl;

	//Define a list of images to be saved
	std::vector<ShortImageType::Pointer> inputImages;

	std::cout << "Read Dicom images in " << inputPath << std::endl;
	double positionZImage1 = 0., positionZImage2 = 0.;
	double spacingXY = 0.;
	for (int i = 0; i < listOfFiles.size(); ++i)
	{
		//try to read the ITK file and save the image - ITK ex4 and ex5
		try
		{
			//Create ITK reader & GDCMImageIO

			//Save read image in the list
			

			//For the first two images, we get the image position (0020, 0032).
			//From the difference, we compute the spacingZ
/*			if (i <= 1)
			{
				std::string currentPosition;
				gdcmImageIO->GetValueFromTag(std::string("0020|0032"), currentPosition);

				//image position is at the format "x\y\z", we want to retrieve z position of the 2 first images

				//Split string by \\ and keep last element
				size_t pos = 0;
				size_t endPos = 0;
				std::string delimiter = "\\";
				while ((endPos = currentPosition.find(delimiter, pos)) != std::string::npos)
					pos = endPos + delimiter.length();

				//Convert to double
				const double positionZ = std::stod(currentPosition.substr(pos));
				if (i == 0)
					positionZImage1 = positionZ;
				else positionZImage2 = positionZ;
				
				//For first image, check spacing under format spacingX\spacingY
				//Spacing tag is (0028, 0030)
				std::string spacingStr;
				gdcmImageIO->GetValueFromTag(std::string("0028|0030"), spacingStr);

				//Split string by \\ and keep first element
				spacingXY = std::stod(spacingStr.substr(0, spacingStr.find(delimiter, 0)));
			}
*/
		}
		//In case of non-image file
		catch (itk::ExceptionObject& ex)
		{
			std::cout << "Error with file " << listOfFiles[i] << ":" << ex.what();
		}
	}

	std::cout << inputImages.size() << " images read." << std::endl;

	//Get dimension X/Y/Z
	Dimensions dimensions;
	//dimensions.x = ...
	//...
	//std::cout << "Dimensions: [" << dimensionX << ", " << dimensionY << ", " << dimensionZ << "]" << std::endl;

	//Get spacing X/Y/Z
	//...
	//std::cout << "Spacing: [" << spacingX << ", " << spacingY << ", " << spacingZ << "]" << std::endl;


	//Build the vtkImageData containing the raw volume - VTK Ex12
	vtkSmartPointer<vtkImageData> rawVTKData = vtkSmartPointer<vtkImageData>::New();
	//rawVTKData->SetDimensions(...
	//rawVTKData->SetSpacing(...
	
	//Create scalars to fill the vtkImageData
	vtkSmartPointer<vtkShortArray> scalars = vtkSmartPointer<vtkShortArray>::New();
	//scalars->SetNumberOfValues(...

	int offset = 0;
	std::cout << "Apply thresholding on raw images" << std::endl;
	//Iterate over all images and fill the scalars
	for (int z = 0; z < inputImages.size(); ++z)
	{
		//Create iterator on current image - ITK Ex3
		// In the while, set the value of each pixel to the scalars using offset
		
	}

	rawVTKData->GetPointData()->SetScalars(scalars);

	//We need to flip AxisY between ITK and VTK doesn't have the same based referentiel
	vtkSmartPointer<vtkImageFlip> flipper = vtkSmartPointer<vtkImageFlip>::New();
	flipper->SetFilteredAxis(1);
	flipper->SetInputData(rawVTKData);
	flipper->Update();

	rawVTKData = flipper->GetOutput();

	//Now we want to segment the data
	std::cout << "Creating scapula mesh" << std::endl;
	//vtkPolyData* scapula = segmentData(...

	//Segment from 0 to 1 for Humerus
	std::cout << "Creating humerus mesh" << std::endl;
	//vtkPolyData* humerus = segmentData(...


	// ----------- DISPLAY ---------------

	// Create mappers & actors

	// Create renderer

	// Set background color

	// Create render window
	// 
	// Associate the renderer to the window

	// Create window interactor
	// 
	// Add actors to renderer

	// Start rendering

	// Start interactor

	return 0;
}
