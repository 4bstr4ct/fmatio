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

#if 0

#include <fmatio.hpp>
#include <fmatio/std/utilities.hpp>

using namespace ::fmatio;

int main(int argc, char** argv)
{
	echo(::std::cout, "{}\n", 5);
	echo(::std::cout, "{}\n", 7);
	echo(::std::cout, "{}\n", 7u);
	echo(::std::cout, "{}\n", 4.5f);
	echo(::std::cout, "{}\n", 2.25);
	echo(::std::cout, "{}\n", -1);
	echo(::std::cout, "{}\n", 'h');
	echo(::std::cout, "{}\n", 't');
	echo(::std::cout, "{}\n", (char*)"hello");
	echo(::std::cout, "{}\n", (char*)"yeyeye!");
	echo(::std::cout, "{}\n", nullptr);
	return 0;
}

#else

#include "./fmatio_all_v1.0.1.hpp"

using namespace ::fmatio;

int main(int argc, char** argv)
{
	echo(::std::cout, "{}\n", 5);
	echo(::std::cout, "{}\n", 7);
	echo(::std::cout, "{}\n", 7u);
	echo(::std::cout, "{}\n", 4.5f);
	echo(::std::cout, "{}\n", 2.25);
	echo(::std::cout, "{}\n", -1);
	echo(::std::cout, "{}\n", 'h');
	echo(::std::cout, "{}\n", 't');
	echo(::std::cout, "{}\n", (char*)"hello");
	echo(::std::cout, "{}\n", (char*)"yeyeye!");
	echo(::std::cout, "{}\n", nullptr);
	return 0;
}

#endif // 1
