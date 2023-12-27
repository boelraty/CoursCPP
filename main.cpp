//-------------------------------------------------------------------------------------------------------------------
/*!	\brief	Ex final
*	\file	main.cpp
*///-----------------------------------------------------------------------------------------------------------------

/*---- STD Includes ----*/
#include <filesystem>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>

/*---- ITK Includes ----*/
#include <itkBinaryThresholdImageFilter.h>
#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkGDCMImageIO.h>
#include <itkImageRegionConstIterator.h>

/*---- VTK Includes ----*/
#include <vtkActor.h>
#include <vtkImageData.h>
#include <vtkImageFlip.h>
#include <vtkMarchingCubes.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkShortArray.h>
#include <vtkSmartPointer.h>

//Define image types
typedef itk::Image<signed short, 2> ShortImageType;
typedef itk::Image<unsigned char, 2 > UCharImageType;

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
	std::vector<UCharImageType::Pointer> outputImages;
	//Apply threshold on each raw images - ITK Ex6
	//Same as ITKReader with itk::BinaryThresholdImageFilter
	for (unsigned int z = 0; z < p_inputImages.size(); ++z) 
	{
		//Create thresholder and save output in a list if images                         
		typedef itk::BinaryThresholdImageFilter< ShortImageType, UCharImageType> Thresholder;

		Thresholder::Pointer thresholder = Thresholder::New();

		thresholder->SetLowerThreshold(p_lowerThreshold);
		thresholder->SetUpperThreshold(p_upperThreshold);
		thresholder->SetInput(p_inputImages[z]);
		thresholder->Update(); 

		//Save images in a list
		outputImages.push_back(thresholder->GetOutput());

	}

	//Build Image Data for input of marching cubes - VTK Ex12 and prior exemples with raw images
	
	// Create vtkImageData
	vtkSmartPointer<vtkImageData> data = vtkSmartPointer<vtkImageData>::New();
	data->SetDimensions(p_dimensions.x, p_dimensions.y, p_dimensions.z);
	data->SetSpacing(p_spacing.x, p_spacing.y, p_spacing.z);

	// Fill the image data
	vtkSmartPointer<vtkUnsignedCharArray> scalars = vtkSmartPointer<vtkUnsignedCharArray>::New();
	scalars->SetNumberOfValues(p_dimensions.x * p_dimensions.y * p_dimensions.z);


	int offset = 0;
	//Iterate over all images and fill the scalars
	for (unsigned int z = 0; z < outputImages.size(); ++z)
	{
		//Create iterator on current image - ITK Ex3
		// In the while, set the value of each pixel to the scalars using offset
		itk::ImageRegionConstIterator<UCharImageType> it
		(outputImages[z], outputImages[z]->GetLargestPossibleRegion());

		//Initialise iterator to begin
		it.GoToBegin();

		while (!it.IsAtEnd())//iterateur is at end
		{
			scalars->SetValue(offset, it.Get());
			//increment iterator
			++it;
			++offset;
		}
	}

	data->GetPointData()->SetScalars(scalars);

	//Create mesh related to image data
	vtkSmartPointer<vtkMarchingCubes> marchingCubes = vtkSmartPointer<vtkMarchingCubes>::New();
	marchingCubes->SetInputData(data);
	marchingCubes->SetValue(0, 1);
	marchingCubes->Update();

	//Return resulting mesh
	vtkPolyData* mesh = vtkPolyData::New();
	mesh->DeepCopy(marchingCubes->GetOutput());

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
	std::sort(listOfFiles.begin(), listOfFiles.end());
	std::cout << "Number of files found: " << listOfFiles.size() << std::endl;

	//Define a list of images to be saved
	std::vector<ShortImageType::Pointer> inputImages;

	std::cout << "Read Dicom images in " << inputPath << std::endl;
	double positionZImage1 = 0., positionZImage2 = 0.;
	double spacingXY = 0.;
	for (unsigned int i = 0; i < listOfFiles.size(); ++i)
	{
		//try to read the ITK file and save the image - ITK ex5
		try
		{
			//std::cout << "Read image " << i << " at location: " << listOfFiles[i] << std::endl;
			//Create ITK reader & GDCMImageIO
			itk::GDCMImageIO::Pointer gdcmImageIO = itk::GDCMImageIO::New();

			//Create the reader to read an image
			itk::ImageFileReader<ShortImageType>::Pointer reader
				= itk::ImageFileReader<ShortImageType>::New();
			reader->SetFileName(listOfFiles[i]);
			reader->SetImageIO(gdcmImageIO);
			reader->Update();
			
			//Save read image in the list
			inputImages.push_back(reader->GetOutput());

			//For the first two images, we get the image position (0020, 0032).
			//From the difference, we compute the spacingZ
			if (i <= 1)
			{
				std::string currentPosition;
				gdcmImageIO->GetValueFromTag(std::string("0020|0032"), currentPosition);
				std::cout << "Position image " << i << ": " << currentPosition << std::endl;
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
				std::cout << "Spacing field: " << spacingStr << std::endl;
				//Split string by \\ and keep first element
				spacingXY = std::stod(spacingStr.substr(0, spacingStr.find(delimiter, 0)));
			}

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
	dimensions.x = inputImages[0]->GetLargestPossibleRegion().GetSize()[0];
	dimensions.y = inputImages[0]->GetLargestPossibleRegion().GetSize()[1];
	dimensions.z = inputImages.size();
	std::cout << "Dimensions: [" << dimensions.x << ", " << dimensions.y << ", " << dimensions.z << "]" << std::endl;

	//Get spacing X/Y/Z
	Spacing spacing;
	spacing.x = spacingXY;
	spacing.y = spacingXY;
	spacing.z = fabs(positionZImage1 - positionZImage2);
	std::cout << "Spacing: [" << spacing.x << ", " << spacing.y << ", " << spacing.z << "]" << std::endl;


	//Build the vtkImageData containing the raw volume - VTK Ex12
	vtkSmartPointer<vtkImageData> rawVTKData = vtkSmartPointer<vtkImageData>::New();
	rawVTKData->SetDimensions(dimensions.x, dimensions.y, dimensions.z);
	rawVTKData->SetSpacing(spacing.x, spacing.y, spacing.z);
	
	//Create scalars to fill the vtkImageData
	vtkSmartPointer<vtkShortArray> scalars = vtkSmartPointer<vtkShortArray>::New();
	scalars->SetNumberOfValues(dimensions.x * dimensions.y * dimensions.z);

	int offset = 0;
	std::cout << "Apply thresholding on raw images" << std::endl;
	//Iterate over all images and fill the scalars
	for (int z = 0; z < inputImages.size(); ++z)
	{
		//Create iterator on current image - ITK Ex3
		// In the while, set the value of each pixel to the scalars using offset
		itk::ImageRegionConstIterator<ShortImageType> it
		(inputImages[z], inputImages[z]->GetLargestPossibleRegion());

		//Initialize iterator to beginning
		it.GoToBegin();

		while (!it.IsAtEnd()) //Iterator IsAtEnd()
		{
			scalars->SetValue(offset, it.Get());
			//Increment iterator
			++it;
			++offset;
		}
	}

	rawVTKData->GetPointData()->SetScalars(scalars);

	//Now we want to segment the data
	std::cout << "Creating scapula mesh" << std::endl;
	vtkPolyData* scapula = segmentData(inputImages, 1, 1, dimensions, spacing);

	//Segment from 0 to 1 for Humerus
	std::cout << "Creating humerus mesh" << std::endl;
	vtkPolyData* humerus = segmentData(inputImages, 2, 2, dimensions, spacing);


	// ----------- DISPLAY ---------------

	// Create mappers & actors
	vtkSmartPointer<vtkPolyDataMapper> mapperScapula = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapperScapula->SetInputData(scapula); 
	mapperScapula->ScalarVisibilityOff();

	vtkSmartPointer<vtkActor> actorScapula = vtkSmartPointer<vtkActor>::New();
	actorScapula->SetMapper(mapperScapula);
	actorScapula->GetProperty()->SetColor(0.87, 0.83, 0.69);

	vtkSmartPointer<vtkPolyDataMapper> mapperHumerus = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapperHumerus->SetInputData(humerus);
	mapperHumerus->ScalarVisibilityOff();

	vtkSmartPointer<vtkActor> actorHumerus = vtkSmartPointer<vtkActor>::New();
	actorHumerus->SetMapper(mapperHumerus);
	actorHumerus->GetProperty()->SetColor(0.87, 0.83, 0.69);

	// Create renderer
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();

	// Set background color
	renderer->SetBackground(1, 1, 1);

	// Add actors to renderer
	renderer->AddActor(actorScapula);
	renderer->AddActor(actorHumerus);

	// Create render window
	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	
	// Associate the renderer to the window
	renderWindow->AddRenderer(renderer);

	// Create window interactor
	vtkSmartPointer<vtkRenderWindowInteractor> interactorWindow = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactorWindow->SetRenderWindow(renderWindow);

	// Start rendering
	renderWindow->Render();
	
	// Start interactor
	interactorWindow->Start();

	return 0;
}
