/*******************************************************************************
 * @file fmatio.hpp
 * 
 * @author Joris Baranauskas (jorisb)
 * 
 * Main library header. It includes most often used and important
 * headers and defines main library methods.
 * 
 * @copyright © 2022-2023 by Joris Baranauskas
 * 
 * This file are distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.
 * You should have received a copy of the license along with this project.
 * If not, see https://www.gnu.org/licenses/.
 ******************************************************************************/

#ifndef FMATIO_INCLUDE_FMATIO_HPP
#define FMATIO_INCLUDE_FMATIO_HPP

#include <fmatio/core.hpp>

#include <sstream>
#include <string>
#include <vector>

namespace fmatio
{
	void hello();

	template<typename Arg, typename... Args>
	FMATIO_API ::std::string format(const ::std::string& pattern, const Arg& arg, Args&&... args) noexcept;

	template<typename Stream, typename... Args>
	FMATIO_API void print(Stream& stream, const ::std::string& pattern, Args&&... args) noexcept;
}

namespace fmatio
{
	template<typename Arg>
	FMATIO_API ::std::string process(Arg&& arg) noexcept
	{
		::std::stringstream stream = ::std::stringstream();
		stream << arg;
		return stream.str();
	}

	FMATIO_API ::std::vector<::std::string> generate() noexcept
	{
		return {};
	}

	template<typename Arg, typename... Args>
	FMATIO_API ::std::vector<::std::string> generate(const Arg& arg, Args&&... args) noexcept
	{
		::std::vector<::std::string> values = ::std::vector<::std::string>();
		values.push_back(process(arg));
		
		const ::std::vector<::std::string>& remainder = generate(args...);

		for (const ::std::string& value : remainder)
			values.push_back(process(value));

		return values;
	}

	FMATIO_API ::std::string format(const ::std::string& pattern) noexcept
	{
		return pattern;
	}

	template<typename Arg, typename... Args>
	FMATIO_API ::std::string format(const ::std::string& pattern, const Arg& arg, Args&&... args) noexcept
	{
		::std::stringstream stream = ::std::stringstream();
		stream << pattern;

		const ::std::vector<::std::string>& values = generate(arg, ::std::forward<Args>(args)...);

		for (const ::std::string& value : values)
			stream << value << " ";
		
		return stream.str();
	}

	template<typename Stream, typename... Args>
	FMATIO_API void print(Stream& stream, const ::std::string& pattern, Args&&... args) noexcept
	{
		stream << format(pattern, ::std::forward<Args>(args)...);
	}
}

#endif
