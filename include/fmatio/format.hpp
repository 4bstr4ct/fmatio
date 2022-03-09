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

#include <fmatio/core.hpp>
#include <fmatio/types.hpp>

#include <fmatio/basic_string.hpp>
#include <fmatio/basic_string_view.hpp>

#include <fmatio/details/writers.hpp>
#include <fmatio/details/arguments.hpp>

namespace fmatio
{
	template<typename Char>
	void formatHandle(details::BasicFormatWriter<Char>& writer, BasicStringView<Char> pattern, const details::BasicFormatArgumentsList<Char>& arguments) FMATIO_NOEXCEPT;

	template<typename Result, typename Pattern, typename... Arguments>
	Result format(const Pattern& pattern, Arguments&&... arguments) FMATIO_NOEXCEPT;

	template<typename Pattern, typename... Arguments>
	BasicString<char> format(const Pattern& pattern, Arguments&&... arguments) FMATIO_NOEXCEPT;

	template<typename Pattern, typename... Arguments>
	BasicString<wchar> wformat(const Pattern& pattern, Arguments&&... arguments) FMATIO_NOEXCEPT;

	template<typename Stream, typename Pattern, typename... Arguments>
	void echo(Stream& stream, const Pattern& pattern, Arguments&&... arguments) FMATIO_NOEXCEPT;
}

#include "./format.inl"

#endif
