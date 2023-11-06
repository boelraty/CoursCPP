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
#include <vtkSTLReader.h>
#include <vtkSTLWriter.h>
#include <vtkCutter.h>
#include <vtkPlane.h>



int main(int p_argc, char* p_argv[])
{
	vtkSmartPointer<vtkSTLReader> readerScapula = vtkSmartPointer<vtkSTLReader>::New();
	readerScapula->SetFileName("C:/Users/vsimoes/ownCloud/CoursISEN/Data/scapula.stl");
	readerScapula->Update();

	vtkSmartPointer<vtkPlane> plane = vtkSmartPointer<vtkPlane>::New();
	plane->SetNormal(0, 0, 1);
	plane->SetOrigin(0, 0, 0);

	vtkSmartPointer<vtkCutter> cutter = vtkSmartPointer<vtkCutter>::New();
	cutter->SetCutFunction(plane);
	cutter->SetInputData(readerScapula->GetOutput());
	cutter->Update();

	vtkSmartPointer<vtkPlane> plane2 = vtkSmartPointer<vtkPlane>::New();
	plane2->SetNormal(1, 0, 0);
	plane2->SetOrigin(0, 0, 0);

	vtkSmartPointer<vtkCutter> cutter2 = vtkSmartPointer<vtkCutter>::New();
	cutter2->SetCutFunction(plane2);
	cutter2->SetInputData(readerScapula->GetOutput());
	cutter2->Update();

	vtkSmartPointer<vtkPlane> plane3 = vtkSmartPointer<vtkPlane>::New();
	plane3->SetNormal(1, 1, 0);
	plane3->SetOrigin(0, 0, 0);

	vtkSmartPointer<vtkCutter> cutter3 = vtkSmartPointer<vtkCutter>::New();
	cutter3->SetCutFunction(plane3);
	cutter3->SetInputData(readerScapula->GetOutput());
	cutter3->Update();

	vtkSmartPointer<vtkSTLReader> readerHumerus = vtkSmartPointer<vtkSTLReader>::New();
	readerHumerus->SetFileName("C:/Users/vsimoes/ownCloud/CoursISEN/Data/humerus.stl");
	readerHumerus->Update();

	vtkSmartPointer<vtkPolyDataMapper> mapperScapula = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapperScapula->SetInputData(readerScapula->GetOutput());
	vtkSmartPointer<vtkPolyDataMapper> mapperHumerus = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapperHumerus->SetInputData(readerHumerus->GetOutput());
	vtkSmartPointer<vtkPolyDataMapper> mapperCutter = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapperCutter->SetInputData(cutter->GetOutput());;
	vtkSmartPointer<vtkPolyDataMapper> mapperCutter2 = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapperCutter2->SetInputData(cutter2->GetOutput());
	vtkSmartPointer<vtkPolyDataMapper> mapperCutter3 = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapperCutter3->SetInputData(cutter3->GetOutput());

	vtkSmartPointer<vtkActor> actorScapula = vtkSmartPointer<vtkActor>::New();
	actorScapula->SetMapper(mapperScapula);
	actorScapula->GetProperty()->SetColor(0.87, 0.83, 0.69);
	actorScapula->GetProperty()->SetOpacity(0.5);
	vtkSmartPointer<vtkActor> actorHumerus = vtkSmartPointer<vtkActor>::New();
	actorHumerus->SetMapper(mapperHumerus);
	actorHumerus->GetProperty()->SetColor(0.87, 0.83, 0.69);
	vtkSmartPointer<vtkActor> actorCutter = vtkSmartPointer<vtkActor>::New();
	actorCutter->SetMapper(mapperCutter);
	actorCutter->GetProperty()->SetColor(1, 0, 0);
	vtkSmartPointer<vtkActor> actorCutter2 = vtkSmartPointer<vtkActor>::New();
	actorCutter2->SetMapper(mapperCutter2);
	actorCutter2->GetProperty()->SetColor(0, 1, 0);
	vtkSmartPointer<vtkActor> actorCutter3 = vtkSmartPointer<vtkActor>::New();
	actorCutter3->SetMapper(mapperCutter3);
	actorCutter3->GetProperty()->SetColor(0, 0, 1);
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
	//renderer->AddActor(actorScapula);
	renderer->AddActor(actorHumerus);
	renderer->AddActor(actorCutter);
	renderer->AddActor(actorCutter2);
	renderer->AddActor(actorCutter3);
	// Start rendering
	renderWindow->Render();

	// Start interactor
	interactorWindow->Start();

	return 0;
}
