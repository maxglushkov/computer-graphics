#include <iostream>
#include "ice-application.hpp"

int main()
{
	try
	{
		ICEApplication().Run();
		return 0;
	}
	catch (std::exception const& ex)
	{
		std::cerr << "Fatal error: " << ex.what() << '\n';
		return 1;
	}
}
