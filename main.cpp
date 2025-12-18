//-------------------------------------------------------------------------------------------------------------------
/*!	\brief	Exemple1
*	\file	main.cpp
*///-----------------------------------------------------------------------------------------------------------------

/*---- VTK Includes ----*/
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCamera.h>
#include <vtkLight.h>
#include <vtkProperty.h>
#include <vtkAxesActor.h>
#include <vtkSTLWriter.h>
#include <vtkSTLReader.h>


int main(int p_argc, char* p_argv[])
{
	vtkSmartPointer<vtkSTLReader> reader1 = vtkSmartPointer<vtkSTLReader>::New();
	reader1->SetFileName("C:/Users/vsimoes/OneDrive - Stryker/Documents/CoursISEN/Data/scapula.stl");
	reader1->Update();
	
	vtkSmartPointer<vtkPolyDataMapper> mapper1 = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper1->SetInputData(reader1->GetOutput());

	vtkSmartPointer<vtkActor> actor1 = vtkSmartPointer<vtkActor>::New();
	actor1->SetMapper(mapper1);
	actor1->GetProperty()->SetColor(0.87, 0.83, 0.69);

	vtkSmartPointer<vtkSTLReader> reader2 = vtkSmartPointer<vtkSTLReader>::New();
	reader2->SetFileName("C:/Users/vsimoes/OneDrive - Stryker/Documents/CoursISEN/Data/humerus.stl");
	reader2->Update();

	vtkSmartPointer<vtkPolyDataMapper> mapper2 = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper2->SetInputData(reader2->GetOutput());

	vtkSmartPointer<vtkActor> actor2 = vtkSmartPointer<vtkActor>::New();
	actor2->SetMapper(mapper2);
	actor2->GetProperty()->SetColor(0.87, 0.83, 0.69);


	// Create renderer - ex2
	vtkSmartPointer<vtkRenderer> scene = vtkSmartPointer<vtkRenderer>::New();
	// Set background color - SetBackgroundColor(R[0-1],G[0-1],B[0-1]);
	scene->SetBackground(1, 1, 1);

	// Add Actor to scene
	scene->AddActor(actor1);
	scene->AddActor(actor2);

	// Create render window
	vtkSmartPointer<vtkRenderWindow> window = vtkSmartPointer<vtkRenderWindow>::New();
	// Associate the renderer to the window - Add renderer method
	window->AddRenderer(scene);

	vtkSmartPointer<vtkRenderWindowInteractor> interactor 
		= vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(window);

	// Start rendering - Method Render()
	window->Render();
	
	interactor->Start();
	
	return 0;
} 
