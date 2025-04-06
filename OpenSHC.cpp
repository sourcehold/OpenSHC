
#include <iostream>

// We turn optimization off to make sure functions mentioned here aren't inlined
#pragma optimize("", off)

int main(int argc, char** argv)
{
	std::cout << "Welcome to OpenSHC!" << std::endl;

// Here we refer to pieces of code that we don't want to have optimized away
	return 0;
}
