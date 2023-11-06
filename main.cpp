//-------------------------------------------------------------------------------------------------------------------
/*!	\brief	Exemple7
*	\file	main.cpp
*///-----------------------------------------------------------------------------------------------------------------

/*---- VTK Includes ----*/
#include <vtkActor.h>
#include <vtkAxesActor.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkCubeSource.h>



int main(int p_argc, char* p_argv[])
{
	// Create a cube
	vtkSmartPointer<vtkCubeSource> cubeObject = vtkSmartPointer<vtkCubeSource>::New();
	cubeObject->SetCenter(0, 0, 0);
	cubeObject->SetXLength(50);
	cubeObject->SetYLength(100);
	cubeObject->SetZLength(200);
	cubeObject->Update();

	// Create mapper for the sphere
	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(cubeObject->GetOutput());

	// Create actor related to previous mapper
	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	actor->GetProperty()->SetOpacity(0.4);

	// Create actor to display the axis
	vtkSmartPointer<vtkAxesActor> axesActor = vtkSmartPointer<vtkAxesActor>::New();
	axesActor->SetTotalLength(100, 100, 100);
	//axesActor->AxisLabelsOff();

	vtkSmartPointer<vtkTextActor> textActor = vtkSmartPointer<vtkTextActor>::New();
	textActor->SetInput("ISEN");
	textActor->GetTextProperty()->SetColor(1, 0, 1);
	textActor->GetTextProperty()->SetFontSize(30);

	// Create renderer
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();

	// Set background color
	renderer->SetBackground(0.5, 0, 1);

	// Create render window
	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	// Associate the renderer to the window
	renderWindow->AddRenderer(renderer);

	// Create window interactor
	vtkSmartPointer<vtkRenderWindowInteractor> interactorWindow = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactorWindow->SetRenderWindow(renderWindow);

	// Add actor to renderer
	renderer->AddActor(actor);
	// Add axesActor to renderer
	renderer->AddActor(axesActor);
	renderer->AddActor(textActor);

	// Start rendering
	renderWindow->Render();

	// Start interactor
	interactorWindow->Start();

	return 0;
}
