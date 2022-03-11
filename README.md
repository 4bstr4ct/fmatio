# fmatio
C++ header-only formatting library.

## About
fmatio is a lightweight C++ header-only formatting library. It offers cross-platform compatibility, little-to-no dependence on the c++ standards, and reasonable speed. This library is made with speed in mind and a small layer of abstraction. Note: most of the requirements are not yet implemented and/or available - the library is still in preliminary development.

Regarding independence for c++ standards, many data structures, such as basic string, basic string view, and others are reimplemented in a way that is optimized for library usage. These data structures can be used too, but keep in mind - their sole purpose is to optimize the library. Library also contains methods in [std directory](https://github.com/4bstr4ct/fmatio/tree/v1.x/include/fmatio/std) to convert library data structures to their corresponding classes in the standard library.

Currently, there is no plan for introducing the possibility to define formatting rules for user-defined data structures. However, that might change in the future as this library develops.

## Version 1.0.2
Version 1.0.2 contains formatting support for these types:
1. Integers ```::fmatio::format("{} {} {} {}\n", -4, 8u, 0x7f, INT_MAX);```
1. Chars ```::fmatio::format("{} {} {}\n", '8', 'J', 'h');```
1. Booleans ```::fmatio::format("{} {}\n", true, false);```
2. Float and double ```::fmatio::format("{} {}\n", 4.8f, -0.874);```
3. Char pointers (const or not) ```::fmatio::format("{}, {}!\n", (char*)"Hello", (const char*)"world");```
4. Char arays (const or not) ```::fmatio::format("{}, {}!\n", "Hello", "world");```
4. Null pointer ```::fmatio::format("{}!\n", nullptr);```

## Usage
All code that is intended to be used by user is defined in **fmatio** namespace. Every other namespace is mainly used for code that supports main library layer. For using library there is no need to use inner namespaces and code inside them.

**fmatio** can format text and arguments into a custom basic string which
can be transformed into ```std::string``` using std utilites API.
For using **chars** instead of **wchar_t** when formatting, use **cformat** instead of **wformat**. If you decide to use **format**, you must provide result type (currently only library strings are supported: BasicString<char_type> and BasicStringView<char_type>).

```c++
#include <fmatio.hpp>					// For 'format' methods
using ::fmatio::cformat;
#include <fmatio/std/utilities.hpp>		// For casting custom string to standards

#include <string>
using ::std::string;

int main(const int argc, const char** argv)
{
	// Formatting into custom basic string
	BasicString<char> basicString = cformat("A text pattern here with some values: {} and {}!\n", "Hello", 1);
	// Building std string from custom basic string
	string stdString = toStdBasicString(basicString);
	return 0;
}
```

**fmatio** can echo a formatted string to any **output stream** provided.
For using **chars** instead of **wchar_t** when formatting, use **cecho** instead of **wecho**. If you decide to use **echo**, you must provide result type (currently only library strings are supported: BasicString<char_type> and BasicStringView<char_type>).

```c++
#include <fmatio.hpp>		// For 'format' methods
using ::fmatio::cecho;

#include <iostream>			// For cout stream
using ::std::cout;

#include <fstream>			// For ofstream stream
using ::std::ofstream;

int main(const int argc, const char** argv)
{
	// Printing out a formatted string using cout stream
	cecho(cout, "A text pattern here with some values: {} and {}!\n", "Hello", 1);
	// Printing out a formatted string using file output stream
	ofstream stream = ofstream("output.txt");
	cecho(stream, "A text pattern here with some values: {} and {}!\n", "Hello", 1);
	return 0;
}
```

## Future
Next patch update will be focused on:
1. Adding more code examples and documentation.
2. Reworking and optimizing formatter.
3. Adding formatting options (firstly colors).

Next **minor** version update will be focused on:
1. Adding colors, optimized formatters, and formatting options (alignment, color, etc).
2. Performing benchmarks and other tests.

## Copying
This library is distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.
You should have received a copy of the license along with this project.
If not, see https://www.gnu.org/licenses/.

## Authors
Joris Baranauskas