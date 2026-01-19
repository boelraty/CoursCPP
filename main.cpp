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
#include <vtkBooleanOperationPolyDataFilter.h>



int main(int p_argc, char* p_argv[])
{
	// Create a sphere - radius = 50
	vtkSmartPointer<vtkSphereSource> sphereObject = vtkSmartPointer<vtkSphereSource>::New();
	sphereObject->SetCenter(0, 0, 0);
	sphereObject->SetThetaResolution(100);
	sphereObject->SetPhiResolution(100);
	sphereObject->SetRadius(50);
	sphereObject->Update();

	// Create a aphere  - radius = 45
	vtkSmartPointer<vtkSphereSource> sphereObject2 = vtkSmartPointer<vtkSphereSource>::New();
	sphereObject2->SetCenter(60, 0, 0);
	sphereObject2->SetThetaResolution(100);
	sphereObject2->SetPhiResolution(100);
	sphereObject2->SetRadius(40);
	sphereObject2->Update();


	vtkSmartPointer<vtkBooleanOperationPolyDataFilter> booleanFilter
		= vtkSmartPointer<vtkBooleanOperationPolyDataFilter>::New();
	booleanFilter->SetInputData(0, sphereObject->GetOutput());
	booleanFilter->SetInputData(1, sphereObject2->GetOutput());
	booleanFilter->SetOperationToUnion(); //SetOperationToDifference(); SetOperationToUnion();
	booleanFilter->Update();

	// Create mapper for the sphere
	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(booleanFilter->GetOutput());

	// Create actor related to previous mapper
	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	actor->GetProperty()->SetColor(1, 0, 0);

	// Create mapper for the sphere
	vtkSmartPointer<vtkPolyDataMapper> mapperS1 = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapperS1->SetInputData(sphereObject->GetOutput());

	// Create actor related to previous mapper
	vtkSmartPointer<vtkActor> actorS1 = vtkSmartPointer<vtkActor>::New();
	actorS1->SetMapper(mapperS1);
	actorS1->GetProperty()->SetColor(0, 1, 0);
	actorS1->GetProperty()->SetOpacity(0.3);

	// Create mapper for the sphere
	vtkSmartPointer<vtkPolyDataMapper> mapperS2 = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapperS2->SetInputData(sphereObject2->GetOutput());

	// Create actor related to previous mapper
	vtkSmartPointer<vtkActor> actorS2 = vtkSmartPointer<vtkActor>::New();
	actorS2->SetMapper(mapperS2);
	actorS2->GetProperty()->SetColor(0, 0, 1);
	actorS2->GetProperty()->SetOpacity(0.3);

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
	renderer->AddActor(actor);
	//renderer->AddActor(actorS1);
	//renderer->AddActor(actorS2);

	// Start rendering
	renderWindow->Render();

	// Start interactor
	interactorWindow->Start();

	return 0;
}