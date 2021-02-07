//-------------------------------------------------------------------------------------------------------------------
/*!	\brief	Test App
*	\file	main.cpp
*///-----------------------------------------------------------------------------------------------------------------

/*---- ITK Includes ----*/
#include <itkImage.h>

/*---- QT Includes ----*/
#include <qdebug.h>

/*---- VTK Includes ----*/
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>

int main(int p_argc, char* p_argv[])
{
	qDebug() << "Starting test ...";
	
	itk::Image<unsigned char, 2>::Pointer image = itk::Image<unsigned char, 2>::New();
	qDebug() << "ITK OK";

	vtkSmartPointer<vtkPolyData> mesh = vtkSmartPointer<vtkPolyData>::New();
	qDebug() << "VTK OK";

	qDebug() << "QT OK";

	return 0;
} 