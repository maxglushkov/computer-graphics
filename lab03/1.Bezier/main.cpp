#include <iostream>
#include "bezier-application.hpp"

int main()
{
	try
	{
		BezierApplication().Run();
		return 0;
	}
	catch (std::exception const& ex)
	{
		std::cerr << "Fatal error: " << ex.what() << '\n';
		return 1;
	}
}
