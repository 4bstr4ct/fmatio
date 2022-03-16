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

template<typename... Args>
void test(const char* const pattern, Args&&... args)
{
	std::cout << fmatio::format<char>(pattern, fmatio::details::forward<Args>(args)...).getData();
	std::cout << fmatio::cformat(pattern, fmatio::details::forward<Args>(args)...).getData();

	fmatio::echo<char>(std::cout, pattern, fmatio::details::forward<Args>(args)...);
	fmatio::cecho(std::cout, pattern, fmatio::details::forward<Args>(args)...);

	fmatio::BasicString<char> string1 = fmatio::format<char>(pattern, fmatio::details::forward<Args>(args)...);
	fwrite(string1.getData(), sizeof(char), string1.getSize() * sizeof(char), stdout);
	fmatio::BasicString<char> string2 = fmatio::cformat(pattern, fmatio::details::forward<Args>(args)...);
	fwrite(string2.getData(), sizeof(char), string2.getSize() * sizeof(char), stdout);
	
	std::cout << "\n";
}

template<typename Char, typename... Args>
void test(const Char* const pattern, Args&&... args)
{
	std::cout << fmatio::format<Char>(pattern, fmatio::details::forward<Args>(args)...).getData();
	fmatio::echo<Char>(std::cout, pattern, fmatio::details::forward<Args>(args)...);

	fmatio::BasicString<Char> string1 = fmatio::format<Char>(pattern, fmatio::details::forward<Args>(args)...);
	fwrite(string1.getData(), sizeof(Char), string1.getSize() * sizeof(Char), stdout);

	std::cout << "\n";
}

int main(int argc, char** argv)
{
	std::cout << fmatio::format<char>("2 + 2 = {p:2}!\n", 4.0f).getData();

	test("Booleans: {} {}\n", true, false);
	test("8-bit ints: {} {}\n", (fmatio::uint8)0x0, (fmatio::int8)0x1);
	test("16-bit ints: {} {}\n", (fmatio::uint16)16, (fmatio::int16)-17);
	test("32-bit ints: {} {}\n", (fmatio::uint32)20, (fmatio::int32)-18);
	test("64-bit ints: {} {}\n", (fmatio::uint64)11, (fmatio::int64)-65);
	test("Floats: {} {}\n", 5.5f, -3.14f);
	test("Doubles: {} {}\n", 1.25, -2.78);
	test("Chars: {} {} {} {}\n", 'k', '8', '$', '-');
	test("Strings: {} {}{}\n", "Hello", "World", "!");
	test("Nullptr: {}\n", nullptr);
	test("Various: {} {} {} {} {} {} {} {}\n", nullptr, "Hello", 8, -5.5f, 'g', true, 0x7f000100, "Something!");

	test<char>("Booleans: {} {}\n", true, false);
	test<char>("8-bit ints: {} {}\n", (fmatio::uint8)0x0, (fmatio::int8)0x1);
	test<char>("16-bit ints: {} {}\n", (fmatio::uint16)16, (fmatio::int16)-17);
	test<char>("32-bit ints: {} {}\n", (fmatio::uint32)20, (fmatio::int32)-18);
	test<char>("64-bit ints: {} {}\n", (fmatio::uint64)11, (fmatio::int64)-65);
	test<char>("Floats: {} {}\n", 5.5f, -3.14f);
	test<char>("Doubles: {} {}\n", 1.25, -2.78);
	test<char>("Chars: {} {} {} {}\n", 'k', '8', '$', '-');
	test<char>("Strings: {} {}{}\n", "Hello", "World", "!");
	test<char>("Nullptr: {}\n", nullptr);
	test<char>("Various: {} {} {} {} {} {} {} {}\n", nullptr, "Hello", 8, -5.5f, 'g', true, 0x7f000100, "Something!");

	/*
	test<fmatio::wchar>(L"Booleans: {} {}\n", true, false);
	test<fmatio::wchar>(L"8-bit ints: {} {}\n", (fmatio::uint8)0x0, (fmatio::int8)0x1);
	test<fmatio::wchar>(L"16-bit ints: {} {}\n", (fmatio::uint16)16, (fmatio::int16)-17);
	test<fmatio::wchar>(L"32-bit ints: {} {}\n", (fmatio::uint32)20, (fmatio::int32)-18);
	test<fmatio::wchar>(L"64-bit ints: {} {}\n", (fmatio::uint64)11, (fmatio::int64)-65);
	test<fmatio::wchar>(L"Floats: {} {}\n", 5.5f, -3.14f);
	test<fmatio::wchar>(L"Doubles: {} {}\n", 1.25, -2.78);
	test<fmatio::wchar>(L"Chars: {} {} {} {}\n", L'k', L'8', L'$', L'-');
	test<fmatio::wchar>(L"Strings: {} {}{}\n", L"Hello", L"World", L"!");
	test<fmatio::wchar>(L"Nullptr: {}\n", nullptr);
	test<fmatio::wchar>(L"Various: {} {} {} {} {} {} {} {}\n", nullptr, L"Hello", 8, -5.5f, L'g', true, 0x7f000100, L"Something!");
	*/

	std::cout << fmatio::format<char,
		fmatio::BasicArgumentsFormatter<char>,
			fmatio::BasicString<char>>("Hello, {p:2}!\n", 7.0f).getData();

	std::cout << fmatio::format<char,
		fmatio::BasicArgumentsFormatter<char>,
			fmatio::String>("Hello, {p:2}!\n", 7.0f).getData();

	std::cout << fmatio::format<char, fmatio::ArgumentsFormatter, fmatio::String>("Hello, {p:2}!\n", 7.0f).getData();
	std::cout << fmatio::cformat("Hello, {}!\n", "world").getData();

	fmatio::echo<char, fmatio::ArgumentsFormatter, fmatio::String>(std::cout, "Hello, {p:2}!\n", 7.0f);
	fmatio::cecho(std::cout, "Hello, {}!\n", "world");

	return 0;
}
