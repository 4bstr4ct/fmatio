/*******************************************************************************
 * @file basic_string_utilities.hpp
 *
 * @author Joris Baranauskas (jorisb)
 *
 * Defines std functions and operators for basic string.
 *
 * @copyright © 2022-2023 by Joris Baranauskas
 *
 * This file is distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.
 * You should have received a copy of the license along with this project.
 * If not, see https://www.gnu.org/licenses/.
 ******************************************************************************/

#ifndef FMATIO_INCLUDE_FMATIO_STD_BASIC_STRING_UTILITIES_HPP
#define FMATIO_INCLUDE_FMATIO_STD_BASIC_STRING_UTILITIES_HPP

#include <fmatio/core.hpp>
#include <fmatio/basic_string.hpp>

#include <ostream>
#include <string>

template<typename Char = char>
::std::ostream& operator <<(::std::ostream& stream, const fmatio::BasicString<Char>& string) FMATIO_NOEXCEPT
{
	stream << string.getData();
	return stream;
}

template<typename Char>
::std::basic_string<Char> toStdBasicString(const fmatio::BasicString<Char>& string) FMATIO_NOEXCEPT
{
	return ::std::basic_string<Char>(string.getData(), string.getSize());
}

#endif
