//-------------------------------------------------------------------------------------------------------------------
/*!	\brief	Exemple13
*	\file	main.cpp
*///-----------------------------------------------------------------------------------------------------------------

/*---- VTK Includes ----*/
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkCubeSource.h>
#include <vtkSphereSource.h>


int main(int p_argc, char* p_argv[])
{
	// Create a sphere - radius = 50
	//vtkSmartPointer<vtkSphereSource> sphereObject = 

	// Create a aphere  - radius = 45
	//vtkSmartPointer<vtkSphereSource> sphereObject2 = 

	//vtkSmartPointer<vtkBooleanOperationPolyDataFilter> booleanFilter = 

	// Create mapper for the sphere
	//vtkSmartPointer<vtkPolyDataMapper> mapper = 

	// Create actor related to previous mapper
	//vtkSmartPointer<vtkActor> actor = 

	// Create renderer
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();

	// Set background color
	renderer->SetBackground(1, 1, 1);

	// Create renderer
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();

	// Set background color
	renderer->SetBackground(1, 1, 1);

	// Create render window
	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	// Associate the renderer to the window
	renderWindow->AddRenderer(renderer);

	// Create window interactor
	vtkSmartPointer<vtkRenderWindowInteractor> interactorWindow = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactorWindow->SetRenderWindow(renderWindow);

	// Add actor to renderer

	// Start rendering
	renderWindow->Render();

	// Start interactor
	interactorWindow->Start();

	return 0;
}
