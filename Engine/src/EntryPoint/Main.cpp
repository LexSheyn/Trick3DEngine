#include "../PrecompiledHeaders/t3dpch.h"

#include "../Application/FApplication.h"

int32 main()
{
	t3d::FApplication Application;

	try
	{
		Application.Run();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}