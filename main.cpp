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
#include <vtkCutter.h>
#include <vtkPlane.h>

int main(int p_argc, char* p_argv[])
{
	vtkSmartPointer<vtkSTLReader> reader1 = vtkSmartPointer<vtkSTLReader>::New();
	reader1->SetFileName("C:/Users/vsimoes/OneDrive - Stryker/Documents/CoursISEN/Data/scapula.stl");
	reader1->Update();

	vtkSmartPointer<vtkPlane> plane1 = vtkSmartPointer<vtkPlane>::New();
	plane1->SetNormal(0, 0, 1); // transerve	
	vtkSmartPointer<vtkPlane> plane2 = vtkSmartPointer<vtkPlane>::New();
	plane2->SetNormal(1, 1, 0); // coronal
	vtkSmartPointer<vtkPlane> plane3 = vtkSmartPointer<vtkPlane>::New();
	plane3->SetNormal(-1, 1, 0); // sagittal

	vtkSmartPointer<vtkCutter> cutter1 = vtkSmartPointer<vtkCutter>::New();
	cutter1->SetInputData(reader1->GetOutput());
	cutter1->SetCutFunction(plane1);
	cutter1->Update();
	vtkSmartPointer<vtkCutter> cutter2 = vtkSmartPointer<vtkCutter>::New();
	cutter2->SetInputData(reader1->GetOutput());
	cutter2->SetCutFunction(plane2);
	cutter2->Update();
	vtkSmartPointer<vtkCutter> cutter3 = vtkSmartPointer<vtkCutter>::New();
	cutter3->SetInputData(reader1->GetOutput());
	cutter3->SetCutFunction(plane3);
	cutter3->Update();
	
	vtkSmartPointer<vtkPolyDataMapper> mapper1 = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper1->SetInputData(cutter1->GetOutput());

	vtkSmartPointer<vtkActor> actor1 = vtkSmartPointer<vtkActor>::New();
	actor1->SetMapper(mapper1);
	actor1->GetProperty()->SetColor(1, 0, 0);

	vtkSmartPointer<vtkPolyDataMapper> mapper2 = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper2->SetInputData(cutter2->GetOutput());

	vtkSmartPointer<vtkActor> actor2 = vtkSmartPointer<vtkActor>::New();
	actor2->SetMapper(mapper2);
	actor2->GetProperty()->SetColor(0, 1, 0);

	vtkSmartPointer<vtkPolyDataMapper> mapper3 = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper3->SetInputData(cutter3->GetOutput());

	vtkSmartPointer<vtkActor> actor3 = vtkSmartPointer<vtkActor>::New();
	actor3->SetMapper(mapper3);
	actor3->GetProperty()->SetColor(0, 0, 1);

	vtkSmartPointer<vtkSTLReader> reader2 = vtkSmartPointer<vtkSTLReader>::New();
	reader2->SetFileName("C:/Users/vsimoes/OneDrive - Stryker/Documents/CoursISEN/Data/humerus.stl");
	reader2->Update();

	vtkSmartPointer<vtkPolyDataMapper> mapper4 = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper4->SetInputData(reader1->GetOutput());

	vtkSmartPointer<vtkActor> actor4 = vtkSmartPointer<vtkActor>::New();
	actor4->SetMapper(mapper4);
	actor4->GetProperty()->SetColor(0.87, 0.83, 0.69);
	actor4->GetProperty()->SetOpacity(0.4);

	vtkSmartPointer<vtkPolyDataMapper> mapper5 = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper5->SetInputData(reader2->GetOutput());

	vtkSmartPointer<vtkActor> actor5 = vtkSmartPointer<vtkActor>::New();
	actor5->SetMapper(mapper5);
	actor5->GetProperty()->SetColor(0.87, 0.83, 0.69);

	// Create renderer - ex2
	vtkSmartPointer<vtkRenderer> scene = vtkSmartPointer<vtkRenderer>::New();
	// Set background color - SetBackgroundColor(R[0-1],G[0-1],B[0-1]);
	scene->SetBackground(1, 1, 1);

	// Add Actor to scene
	scene->AddActor(actor1);
	scene->AddActor(actor2);
	scene->AddActor(actor3);
	scene->AddActor(actor4);
	scene->AddActor(actor5);

	vtkSmartPointer<vtkAxesActor> axesActor = vtkSmartPointer<vtkAxesActor>::New();
	axesActor->SetTotalLength(50, 50, 50);
	scene->AddActor(axesActor);

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
