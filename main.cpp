//-------------------------------------------------------------------------------------------------------------------
/*!  \brief   Exo final
*    \file    main.cpp
*///-----------------------------------------------------------------------------------------------------------------

/*---- STD Includes ----*/
#include <filesystem>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>

/*---- ITK Includes ----*/
#include <itkImage.h>
#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkGDCMImageIO.h>
#include <itkBinaryThresholdImageFilter.h>
#include <itkImageRegionConstIterator.h>
#include <itkImageRegionIterator.h>

/*---- VTK Includes ----*/
#include <vtkImageData.h>
#include <vtkImageFlip.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkShortArray.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkMarchingCubes.h>

//Define image types
typedef itk::Image<signed short, 2> ShortImageType;

struct Dimensions
{
    int x = 0;
    int y = 0;
    int z = 0;
};

// Define a struct for image spacing
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
    typedef itk::Image<unsigned char, 2> UCharImageType;
    std::vector<UCharImageType::Pointer> imageItk;

    //Apply threshold on each raw images - ITK Ex6
    //Same as ITKReader with itk::BinaryThresholdImageFilter
    // Iterate through each input image to apply binary thresholding
    for (int z = 0; z < p_inputImages.size(); ++z)
    {
        //Create thresholder and save outpout in a list if images

        // Set the lower and upper threshold values

        // Set the input image for thresholding (the zth image of the list)

        // Set the value to assign to pixels inside the threshold range

        // Perform thresholding and update the filter

        // Save thresholded image in vector
        //imageItk.push_back(thresholder->GetOutput());

    }
    //Build Image Data for input of marching cubes - VTK Ex12 and prior exemples with raw images
    vtkSmartPointer<vtkImageData> imageVtk = vtkSmartPointer<vtkImageData>::New();
    imageVtk->SetDimensions(p_dimensions.x, p_dimensions.y, p_dimensions.z);
    imageVtk->SetSpacing(p_spacing.x, p_spacing.y, p_spacing.z);

    // Create scalars to fill the vtkImageData
    vtkSmartPointer<vtkUnsignedCharArray> scalars = vtkSmartPointer<vtkUnsignedCharArray>::New();
    scalars->SetNumberOfValues(p_dimensions.x * p_dimensions.y * p_dimensions.z);

    int offset = 0;

    // Iterate over all images and fill the scalars
    for (int z = 0; z < imageItk.size(); ++z)
    {
        // Create iterator on current image

        //while (!iterator.IsAtEnd()) {

            // Set value of the pixel

            // Increment iterators
        //}
    }
    imageVtk->GetPointData()->SetScalars(scalars);


    //Apply the marching cubes - VTK Ex12

    // Set the input data for the marching cubes algorithm

    // Set the iso-value and generate the surface

    // Return the resulting mesh as vtkPolyData
    vtkPolyData* mesh = vtkPolyData::New();
    vtkSmartPointer<vtkPolyData>::New();

    // DeepCopy is used to create an independent copy of the output of marching cubes
    // This ensures that modifications to the mesh do not affect the original marching cubes output
    //mesh->DeepCopy(marchingcubes->GetOutput());
    return mesh;
}

std::vector<std::string> getListOfFiles(const std::string& p_inputDirectory)
{
    //Search all files in the directory
    std::vector<std::string> listOfFiles;
    /*for (const auto& file : std::filesystem::directory_iterator{ p_inputDirectory })
        listOfFiles.push_back(file.path().string());*/

    std::cout << "Number of files found: " << listOfFiles.size() << std::endl;

    return listOfFiles;
}

double getPositionZ(itk::GDCMImageIO::Pointer p_imageIO)
{
    std::string currentPosition;
    p_imageIO->GetValueFromTag(std::string("0020|0032"), currentPosition);

    //image position is at the format "x\y\z", we want to retrieve z position of the 2 first images

    //Split string by \\ and keep last element
    size_t pos = 0;
    size_t endPos = 0;
    std::string delimiter = "\\";
    while ((endPos = currentPosition.find(delimiter, pos)) != std::string::npos)
        pos = endPos + delimiter.length();

    //Convert to double
    return std::stod(currentPosition.substr(pos));
}

double getSpacingXY(itk::GDCMImageIO::Pointer p_imageIO)
{
    //Check spacing under format spacingX\spacingY
    //Spacing tag is (0028, 0030)
    std::string spacingStr;
    p_imageIO->GetValueFromTag(std::string("0028|0030"), spacingStr);
    std::cout << "spacing field : " << spacingStr << std::endl;

    //Split string by \\ and keep first element
    std::string delimiter = "\\";
    return std::stod(spacingStr.substr(0, spacingStr.find(delimiter, 0)));
}

int main(int p_argc, char* p_argv[])
{
    //Define input path
    const std::string inputPath = "YOUR PATH";

    //Search all files in the directory
    std::vector<std::string> listOfFiles = getListOfFiles(inputPath);

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
            std::cout << "Read image " << i << " at location: " << listOfFiles[i] << std::endl;
            //Create ITK reader & GDCMImageIO

            // Set the file name for the reader to the path of the current DICOM file

            // Set the GDCMImageIO instance as the image IO object for the reader

            // Update the reader to read the image data

            //Save read image in the list
            //inputImages.push_back(reader->GetOutput());

            //For the first two images (i = 0 and i = 1), we get the image position (0020, 0032).
            //From the difference, we compute the spacingZ
            if (i == 0)
            {
                //positionZImage1 = getPositionZ(gdcmImageIO);

                //For first image get spacing X/Y
                //spacingXY = getSpacingXY(gdcmImageIO);
            }
            else if (i == 1)
            {
                //positionZImage2 = getPositionZ(gdcmImageIO);
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
    //dimensions.x = 
    //dimensions.y =
    //dimensions.z =

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


        //Initialize iterator to beginning

        //Iterate
       //while (!it.IsAtEnd()) //Iterator IsAtEnd()
        //{
            //Set value

            //Increment iterators
            //++it;
            ++offset;
        //}
    }

    rawVTKData->GetPointData()->SetScalars(scalars);


    //Now we want to segment the data
    std::cout << "Creating scapula mesh" << std::endl;
    vtkPolyData* scapula;// = segmentData(...);

    //Segment from 0 to 1 for Humerus
    std::cout << "Creating humerus mesh" << std::endl;
    vtkPolyData* humerus;// = segmentData(...);


    // ----------- DISPLAY ---------------

    // Create mappers for the scapula and humerus meshes

    // Create actors for the scapula and humerus meshes


    // Create renderer

    // Set background color

    // Create render window

    // Associate the renderer to the window

    // Create window interactor

    // Add actors to renderer

    // Start rendering
    //renderWindow->Render();

    // Start interactor
    //interactorWindow->Start();

    return 0;
}
