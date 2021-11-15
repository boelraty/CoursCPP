//-------------------------------------------------------------------------------------------------------------------
/*!	\brief	Test App
*	\file	main.cpp
*///-----------------------------------------------------------------------------------------------------------------

/*---- ITK Includes ----*/
#include <itkImage.h>

int main(int p_argc, char* p_argv[])
{
	itk::Image<unsigned char, 2>::Pointer image = itk::Image<unsigned char, 2>::New();
	std::cout << "ITK OK";

	return 0;
} 