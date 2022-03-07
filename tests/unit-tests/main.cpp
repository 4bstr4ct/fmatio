#include <fmatio.hpp>

// #include "./utils.hpp"

#include <stdio.h>
#include <iostream>

using ::fmatio::format;
using ::fmatio::BasicString;
using ::fmatio::BasicStringView;

int main(int argc, char** argv)
{
	// printf("%s", format<BasicStringView>("Hello, from {} {}!\n", "FMATIO", 5).c_str());
	::std::cout << format<BasicString<char>>("Hello, from {} {}!\n", "FMATIO", 5).getData();
	return 0;
}