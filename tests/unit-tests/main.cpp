#include "./utils.hpp"

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
using ::std::ofstream;

struct Point2d
{
	float x, y;
};

#if 1

#include <fmatio.hpp>
#include <fmatio/std/utilities.hpp>

using namespace ::fmatio;

int main(int argc, char** argv)
{
	echo(::std::cout, ": {} {}!\n", 5, (char*)"lalalalala");
	std::string str = toStdBasicString(format(": {} {}!\n", 5, (char*)"lalalalala"));
	std::cout << str; 
	return 0;
}

#else

#include "./fmatio_all.hpp"

using namespace ::fmatio;

int main(int argc, char** argv)
{
	printf("%s", format("Here goes some {random} {numbers : {} {} {} {} {} {}!\n", 5u, 3, 4.5f, -8, 8.987, -0.58f).getData());
	::std::cout << format("Here goes some {random} {numbers : {} {} {} {} {} {}!\n", 5u, 3, 4.5f, -8, 8.987, -0.58f);
	echo(::std::cout, "Here goes some {random} {numbers : {} {} {} {} {} {}!\n", 5u, 3, 4.5f, -8, 8.987, -0.58f);

	return 0;
}

#endif // 1
