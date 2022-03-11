/*******************************************************************************
 * @file format.hpp
 * 
 * @author Joris Baranauskas (jorisb)
 * 
 * Includes most often used and important headers and defines
 * main library methods.
 * 
 * @copyright © 2022-2023 by Joris Baranauskas
 * 
 * This file is distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.
 * You should have received a copy of the license along with this project.
 * If not, see https://www.gnu.org/licenses/.
 ******************************************************************************/

#ifndef FMATIO_INCLUDE_FMATIO_FORMAT_HPP
#define FMATIO_INCLUDE_FMATIO_FORMAT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#	pragma once
#endif

#include <fmatio/core.hpp>
#include <fmatio/types.hpp>

#include <fmatio/basic_string.hpp>
#include <fmatio/basic_string_view.hpp>

#include <fmatio/details/writers.hpp>
#include <fmatio/details/arguments.hpp>

namespace fmatio
{
	template<typename Char>
	FMATIO_INLINE void formatHandle(details::BasicFormatWriter<Char>& writer, BasicStringView<Char> pattern, const details::BasicFormatArgumentsList<Char>& arguments) FMATIO_NOEXCEPT;

	template<typename Result, typename Pattern, typename... Arguments>
	FMATIO_INLINE Result format(const Pattern& pattern, Arguments&&... arguments) FMATIO_NOEXCEPT;

	template<typename Pattern, typename... Arguments>
	FMATIO_INLINE BasicString<char> cformat(const Pattern& pattern, Arguments&&... arguments) FMATIO_NOEXCEPT;

	template<typename Pattern, typename... Arguments>
	FMATIO_INLINE BasicString<wchar> wformat(const Pattern& pattern, Arguments&&... arguments) FMATIO_NOEXCEPT;

	template<typename Result, typename Stream, typename Pattern, typename... Arguments>
	FMATIO_INLINE void echo(Stream& stream, const Pattern& pattern, Arguments&&... arguments) FMATIO_NOEXCEPT;

	template<typename Pattern, typename Stream, typename... Arguments>
	FMATIO_INLINE void cecho(Stream& stream, const Pattern& pattern, Arguments&&... arguments) FMATIO_NOEXCEPT;

	template<typename Pattern, typename Stream, typename... Arguments>
	FMATIO_INLINE void wecho(Stream& stream, const Pattern& pattern, Arguments&&... arguments) FMATIO_NOEXCEPT;
}

#include "./format.inl"

#endif
