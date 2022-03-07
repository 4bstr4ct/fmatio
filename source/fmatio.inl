/*******************************************************************************
 * @file fmatio.inl
 * 
 * @author Joris Baranauskas (jorisb)
 * 
 * Defines fmatio.hpp implementations.
 * 
 * @copyright © 2022-2023 by Joris Baranauskas
 * 
 * This file are distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.
 * You should have received a copy of the license along with this project.
 * If not, see https://www.gnu.org/licenses/.
 ******************************************************************************/

#include <iostream>

namespace fmatio
{
	template<typename>
	FMATIO_API ::std::string format(const StringView& pattern) noexcept
	{
		return ::std::string(pattern.getData());
	}

	template<typename... Args>
	FMATIO_API ::std::string format(const StringView& pattern, Args&&... args) noexcept
	{
		ArgumentsList<Args&&...> argumentsList = ArgumentsList<Args&&...>(::std::forward<Args>(args)...);
		Formatter<Args&&...> formatter = Formatter<Args&&...>(pattern, argumentsList);
		return formatter.format();
	}

	template<typename Stream, typename... Args>
	FMATIO_API void echo(Stream& stream, const StringView& pattern, Args&&... args) noexcept
	{
		stream << format(pattern, ::std::forward<Args>(args)...);
	}

	template<typename... Args>
	FMATIO_API void print(const StringView& pattern, Args&&... args) noexcept
	{
		::std::cout << format(pattern, ::std::forward<Args>(args)...);
	}
}
