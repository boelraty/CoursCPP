//-------------------------------------------------------------------------------------------------------------------
/*!	\brief	Exemple1
*	\file	main.cpp
*///-----------------------------------------------------------------------------------------------------------------

/*---- VTK Includes ----*/
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>

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
	
	
	// Create renderer - ex2
	//vtkSmartPointer<vtkRenderer> renderer =
	// Set background color - SetBackgroundColor(R[0-1],G[0-1],B[0-1]);

	// Create render window
	//vtkSmartPointer<vtkRenderWindow> renderWindow = 
	// Associate the renderer to the window - Add renderer method


	// Start rendering - Method Render()
	
	
	return 0;
} 
