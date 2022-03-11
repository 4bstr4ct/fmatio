/*******************************************************************************
 * @file basic_string_view_utilities.hpp
 *
 * @author Joris Baranauskas (jorisb)
 *
 * Defines std functions and operators for basic string view.
 *
 * @copyright © 2022-2023 by Joris Baranauskas
 *
 * This file is distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.
 * You should have received a copy of the license along with this project.
 * If not, see https://www.gnu.org/licenses/.
 ******************************************************************************/

#ifndef FMATIO_INCLUDE_FMATIO_STD_BASIC_STRING_VIEW_UTILITIES_HPP
#define FMATIO_INCLUDE_FMATIO_STD_BASIC_STRING_VIEW_UTILITIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#	pragma once
#endif

#include <fmatio/core.hpp>
#include <fmatio/basic_string_view.hpp>

#include <ostream>
#include <string>

template<typename Char = char>
FMATIO_INLINE ::std::ostream& operator <<(::std::ostream& stream, const fmatio::BasicStringView<Char>& stringView) FMATIO_NOEXCEPT
{
	stream << stringView.getData();
	return stream;
}

template<typename Char>
FMATIO_INLINE ::std::basic_string<Char> toStdBasicString(const fmatio::BasicStringView<Char>& stringView) FMATIO_NOEXCEPT
{
	return ::std::basic_string<Char>(stringView.getData(), stringView.getSize());
}

#endif
