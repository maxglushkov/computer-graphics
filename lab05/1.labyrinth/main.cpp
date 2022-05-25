#include <iostream>
#include "labyrinth-application.hpp"

int main()
{
	try
	{
		LabyrinthApplication().Run();
		return 0;
	}
	catch (std::exception const& ex)
	{
		std::cerr << "Fatal error: " << ex.what() << '\n';
		return 1;
	}
}
