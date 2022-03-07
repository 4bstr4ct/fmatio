#include <fmatio.hpp>

// #include "./utils.hpp"

#include <iostream>

int main(int argc, char** argv)
{
	::std::cout << ::fmatio::format("Hello, from {}!", true, 5, 5.2f) << ::std::endl;
	// ::fmatio::print(::std::cout, "Hello, from {}!", "FMATIO");
	return 0;
}