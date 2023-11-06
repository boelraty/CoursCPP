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
#include <vtkLight.h>
#include <vtkCamera.h>
#include <vtkProperty.h>


int main(int p_argc, char* p_argv[])
{
	// Create a sphere
	vtkSmartPointer<vtkSphereSource> sphereObject 
		= vtkSmartPointer<vtkSphereSource>::New();
	sphereObject->SetCenter(0, 0, 0);
	sphereObject->SetRadius(50);
	sphereObject->SetThetaResolution(100);
	sphereObject->SetPhiResolution(100);
	sphereObject->Update();

	{
		// Get bounds of resulting polydata
		double* bounds = new double[6];
		sphereObject->GetOutput()->GetBounds(bounds);
		std::cout << "Bounds:" << std::endl;
		std::cout << "Xmin: " << bounds[0] << "; Xmax: " << bounds[1] << std::endl;
		std::cout << "Ymin: " << bounds[2] << "; Ymax: " << bounds[3] << std::endl;
		std::cout << "Zmin: " << bounds[4] << "; Zmax: " << bounds[5] << std::endl;//delete [] bounds;
	}

	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(sphereObject->GetOutput());
	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	actor->GetProperty()->SetColor(1, 0, 0);
	actor->GetProperty()->SetOpacity(0.2);

	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->SetBackground(1, 1, 1);
	renderer->AddActor(actor);

/*	vtkSmartPointer<vtkLight> light = vtkSmartPointer<vtkLight>::New();
	light->SetPosition(100, 0, 0);
	light->SetIntensity(1.);
	renderer->AddLight(light);
*/	
	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);

	vtkSmartPointer<vtkRenderWindowInteractor> interactor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(renderWindow);
	
	renderWindow->Render();	
	interactor->Start();

	
	return 0;
}
