#include <fmatio.hpp>

// #include "./utils.hpp"

#include <stdio.h>
#include <iostream>

using ::fmatio::format;
using ::fmatio::echo;
using ::fmatio::BasicString;
using String = ::fmatio::BasicString<char>;
using ::fmatio::BasicStringView;
using ::fmatio::uint32;

struct Point2d
{
	float x, y;
};

int main(int argc, char** argv)
{
	printf("%s", format("Here goes some {random} {numbers : {} {} {} {} {} {}!\n", 5u, 3, 4.5f, -8, 8.987, -0.58f).getData());
	::std::cout << format("Here goes some {random} {numbers : {} {} {} {} {} {}!\n", 5u, 3, 4.5f, -8, 8.987, -0.58f).getData();
	echo(::std::cout, "Here goes some {random} {numbers : {} {} {} {} {} {}!\n", 5u, 3, 4.5f, -8, 8.987, -0.58f);
	return 0;
}