#include <fmatio.hpp>
#include <fmatio/std/utilities.hpp>

#include "./utils.hpp"

#include <stdio.h>
#include <iostream>
#include <string>
#include <array>
#include <vector>

struct Student
{
public:
	std::string firstName;
	std::string lastName;
	float finalGrade;
};

FMATIO_INLINE void test() FMATIO_NOEXCEPT { }

template<typename Arg, typename... Args>
FMATIO_INLINE void test(Arg&& arg, Args&&... args) FMATIO_NOEXCEPT
{
	std::cout << arg << std::endl;
	test(args...);
}


/*

PRODETI TYPEOF SIGNED CHAR*, UNSIGNED CHAR* IR CHAR*!!!!!! 

*/

int main(int argc, char** argv)
{
	test(5, "lalala");

	/*
	fmatio::echo(::std::cout, "{}\n", 5);
	fmatio::echo(::std::cout, "{}\n", 7);
	fmatio::echo(::std::cout, "{}\n", 7u);
	fmatio::echo(::std::cout, "{}\n", 4.5f);
	fmatio::echo(::std::cout, "{}\n", 2.25);
	fmatio::echo(::std::cout, "{}\n", -1);
	fmatio::echo(::std::cout, "{}\n", 'h');
	fmatio::echo(::std::cout, "{}\n", 't');
	fmatio::echo(::std::cout, "{}\n", (char*)"hello");
	fmatio::echo(::std::cout, "{}\n", (char*)"yeyeye!");
	fmatio::echo(::std::cout, "{}\n", nullptr);
	std::cout << fmatio::format("{}\n", 8.5f);
	std::string string = fmatio::format("{}\n", 8.5f).getData();
	std::cout << string;
	*/

	return 0;
}
