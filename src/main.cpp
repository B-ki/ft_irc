#include <iostream>
#include "error.h"

int	main()
{
	std::cout << "Bonjour" << std::endl;
	DEBUG("debug message");
	INFO("info message");
	WARNING("warning message");
	ERROR("error message");
	return 0;
}
