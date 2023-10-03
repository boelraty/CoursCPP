//-------------------------------------------------------------------------------------------------------------------
/*!	\brief	Test App
*	\file	main.cpp
*///-----------------------------------------------------------------------------------------------------------------

/*---- ITK Includes ----*/
#include <itkImage.h>

/*---- VTK Includes ----*/
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>

int main(int p_argc, char* p_argv[])
{
	std::cout << "Starting test ..." << std::endl;
	
	itk::Image<unsigned char, 2>::Pointer image = itk::Image<unsigned char, 2>::New();
	std::cout << "ITK OK" << std::endl;

	vtkSmartPointer<vtkPolyData> mesh = vtkSmartPointer<vtkPolyData>::New();
	std::cout << "VTK OK" << std::endl;

	return 0;
} 