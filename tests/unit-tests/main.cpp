#include <fmatio.hpp>

// #include "./utils.hpp"

#include <iostream>
#include <vector>

template<typename T>
using Vector = ::std::vector<T>;

using ::fmatio::StringView;

int main(int argc, char** argv)
{
	::std::cout << ::fmatio::format("Hello, from {} {}!", "FMATIO", 5) << ::std::endl;
	// ::fmatio::print(::std::cout, "Hello, from {}!", "FMATIO");
	return 0;
}