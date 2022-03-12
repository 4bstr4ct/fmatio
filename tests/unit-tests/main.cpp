#include <fmatio.hpp>
#include <fmatio/formatters.hpp>

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

int main(int argc, char** argv)
{
	fmatio::echo<fmatio::CSafeFmatioFormatter,
		fmatio::String>(
			std::cout, "Hello, {}!\n", "world");

	fmatio::cecho(std::cout, "Hello, {}!\n", "world");

#if 0
	{
		fmatio::echo<fmatio::BasicString<char>>(std::cout, "{}\n", 5);
		fmatio::echo<fmatio::BasicString<char>>(std::cout, "{}\n", 7);
		fmatio::echo<fmatio::BasicString<char>>(std::cout, "{}\n", 7u);
		fmatio::echo<fmatio::BasicString<char>>(std::cout, "{}\n", 4.5f);
		fmatio::echo<fmatio::BasicString<char>>(std::cout, "{}\n", 2.25);
		fmatio::echo<fmatio::BasicString<char>>(std::cout, "{}\n", -1);
		fmatio::echo<fmatio::BasicString<char>>(std::cout, "{}\n", 'h');
		fmatio::echo<fmatio::BasicString<char>>(std::cout, "{}\n", 't');
		fmatio::echo<fmatio::BasicString<char>>(std::cout, "{}\n", (char*)"hello");
		fmatio::echo<fmatio::BasicString<char>>(std::cout, "{}\n", "hello again");
		fmatio::echo<fmatio::BasicString<char>>(std::cout, "{}\n", "lalalalalalala!");
		fmatio::echo<fmatio::BasicString<char>>(std::cout, "{}\n", nullptr);
		std::cout << fmatio::format<fmatio::BasicString<char>>("{}\n", 8.5f);
		std::string string = fmatio::format<fmatio::BasicString<char>>("{}\n", 8.5f).getData();
		const char* temp = string.data();
		std::cout << temp;
		fmatio::BasicString<char> basiString = fmatio::format<fmatio::BasicString<char>>("{}\n", 8.5f);
		const char* cstring = basiString.getData();
		std::cout << cstring;
		const char* cstring2 = fmatio::format<fmatio::BasicString<char>>("{}\n", 8.5f).getData();
		std::cout << cstring2;
	}

	{
		fmatio::cecho(std::cout, "{}\n", 5);
		fmatio::cecho(std::cout, "{}\n", 7);
		fmatio::cecho(std::cout, "{}\n", 7u);
		fmatio::cecho(std::cout, "{}\n", 4.5f);
		fmatio::cecho(std::cout, "{}\n", 2.25);
		fmatio::cecho(std::cout, "{}\n", -1);
		fmatio::cecho(std::cout, "{}\n", 'h');
		fmatio::cecho(std::cout, "{}\n", 't');
		fmatio::cecho(std::cout, "{}\n", (char*)"hello");
		fmatio::cecho(std::cout, "{}\n", "hello again");
		fmatio::cecho(std::cout, "{}\n", "lalalalalalala!");
		fmatio::cecho(std::cout, "{}\n", nullptr);
		std::cout << fmatio::cformat("{}\n", 8.5f);
		std::string string = fmatio::cformat("{}\n", 8.5f).getData();
		const char* temp = string.data();
		std::cout << temp;
		fmatio::BasicString<char> basiString = fmatio::cformat("{}\n", 8.5f);
		const char* cstring = basiString.getData();
		std::cout << cstring;
		const char* cstring2 = fmatio::cformat("{}\n", 8.5f).getData();
		std::cout << cstring2;
	}
#endif

	return 0;
}
