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


int main(int p_argc, char* p_argv[])
{
	// Create a sphere
	typedef vtkSmartPointer<vtkSphereSource> Sphere;
	Sphere sphereObject = Sphere::New();
	sphereObject->SetCenter(20, 30, 40);
	sphereObject->SetRadius(50);
	sphereObject->SetPhiResolution(100);
	sphereObject->SetThetaResolution(100);
	sphereObject->Update();

	// Get bounds of resulting polydata
	double* bounds = sphereObject->GetOutput()->GetBounds();

	std::cout << "Limites: " << bounds[0] << " ; " << bounds[1] << " ; "
		<< bounds[2] << " ; " << bounds[3]
		<< " ; " << bounds[4] << " ; " << bounds[5] << std::endl;

	std::cout << "Nb of points: " << sphereObject->GetOutput()->GetNumberOfPoints() << std::endl;

	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(sphereObject->GetOutput());

	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	actor->GetProperty()->SetColor(1, 0, 1);
	actor->GetProperty()->SetOpacity(0.5);

	vtkSmartPointer<vtkAxesActor> axesActor = vtkSmartPointer<vtkAxesActor>::New();
	axesActor->SetTotalLength(100, 100, 100);

	// Create renderer - ex2
	vtkSmartPointer<vtkRenderer> scene = vtkSmartPointer<vtkRenderer>::New();
	// Set background color - SetBackgroundColor(R[0-1],G[0-1],B[0-1]);
	scene->SetBackground(1, 1, 1);

	// Add Actor to scene
	scene->AddActor(actor);
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
