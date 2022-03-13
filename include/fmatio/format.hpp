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

#include <fmatio/formatters.hpp>

#include <fmatio/details/writers.hpp>
#include <fmatio/details/arguments.hpp>

namespace fmatio
{
	/**
	 * A type represeting basic string of chars.
	 */
	using String = BasicString<char>;
	
	/**
	 * A type represeting basic string of wide chars.
	 */
	using WString = BasicString<wchar>;

	/**
	 * A type represeting basic string view of chars.
	 */
	using StringView = BasicStringView<char>;
	
	/**
	 * A type represeting basic string view of wide chars.
	 */
	using WStringView = BasicStringView<wchar>;

	/**
	 * A type represeting basic arguments formatter of chars.
	 */
	using ArgumentsFormatter = BasicArgumentsFormatter<char>;
	
	/**
	 * A type represeting basic arguments formatter of wide chars.
	 */
	using WArgumentsFormatter = BasicArgumentsFormatter<wchar>;

	/**
	 * Hndle pattern formatting with provided formatter.
	 * 
	 * @tparam Formatter
	 * 		Formatter type.
	 * 
	 * @tparam Char
	 * 		Char type.
	 * 
	 * @param[inout] writer
	 * 		Formatted string writer.
	 *
	 * @param[in] pattern
	 * 		Pattern by which arguments and result will be formatted.
	 *
	 * @param[in] arguments
	 * 		Format arguments list.
	 */
	template<typename Formatter, typename Char>
	FMATIO_INLINE void formatHandle(details::BasicFormatWriter<Char>& writer, BasicStringView<Char> pattern, const details::BasicFormatArgumentsList<Char>& arguments) FMATIO_NOEXCEPT;

	/**
	 * Format arguments using pattern into a provided type of the result.
	 * 
	 * @tparam Formatter
	 * 		Formatter type.
	 *
	 * @tparam Result
	 * 		Result type.
	 *
	 * @tparam Pattern
	 * 		Pattern type.
	 * 
	 * @tparam Arguments
	 * 		Arguments types.
	 *
	 * @param[in] pattern
	 * 		Pattern by which string and arguments will be formatted.
	 * 
	 * @param[in] arguments
	 * 		Format arguments / variables. 
	 * 
	 * @return Result -
	 * 		Formatted string in a type of result. 
	 */
	template<typename Formatter, typename Result, typename Pattern, typename... Arguments>
	FMATIO_INLINE Result format(const Pattern& pattern, Arguments&&... arguments) FMATIO_NOEXCEPT;

	/**
	 * Format arguments using pattern into a basic string pf chars.
	 * 
	 * @tparam Formatter
	 * 		Formatter type.
	 *
	 * @tparam Pattern
	 * 		Pattern type.
	 * 
	 * @tparam Arguments
	 * 		Arguments types.
	 *
	 * @param[in] pattern
	 * 		Pattern by which string and arguments will be formatted.
	 * 
	 * @param[in] arguments
	 * 		Format arguments / variables. 
	 * 
	 * @return BasicString<char> -
	 * 		Formatted string in a type of basic string of chars. 
	 */
	template<typename Formatter = BasicArgumentsFormatter<char>, typename Pattern, typename... Arguments>
	FMATIO_INLINE BasicString<char> cformat(const Pattern& pattern, Arguments&&... arguments) FMATIO_NOEXCEPT;

	/**
	 * Format arguments using pattern into a basic string pf wide chars.
	 * 
	 * @tparam Formatter
	 * 		Formatter type.
	 *
	 * @tparam Pattern
	 * 		Pattern type.
	 * 
	 * @tparam Arguments
	 * 		Arguments types.
	 *
	 * @param[in] pattern
	 * 		Pattern by which string and arguments will be formatted.
	 * 
	 * @param[in] arguments
	 * 		Format arguments / variables. 
	 * 
	 * @return BasicString<wchar> -
	 * 		Formatted string in a type of basic string of wide chars. 
	 */
	template<typename Formatter = BasicArgumentsFormatter<wchar>, typename Pattern, typename... Arguments>
	FMATIO_INLINE BasicString<wchar> wformat(const Pattern& pattern, Arguments&&... arguments) FMATIO_NOEXCEPT;

	/**
	 * Echo formatted string by format function.
	 * 
	 * @tparam Formatter
	 * 		Formatter type.
	 *
	 * @tparam Result
	 * 		Result type.
	 * 
	 * @tparam Stream
	 * 		Stream type.
	 *
	 * @tparam Pattern
	 * 		Pattern type.
	 * 
	 * @tparam Arguments
	 * 		Arguments types.
	 * 
	 * @param[inout] stream
	 * 		Stream to which the formatted string will be passed.
	 * 
	 * @param[in] pattern
	 * 		Pattern by which string and arguments will be formatted.
	 * 
	 * @param[in] arguments
	 * 		Format arguments / variables.
	 */
	template<typename Formatter, typename Result, typename Stream, typename Pattern, typename... Arguments>
	FMATIO_INLINE void echo(Stream& stream, const Pattern& pattern, Arguments&&... arguments) FMATIO_NOEXCEPT;

	/**
	 * Echo formatted string of chars by format function.
	 * 
	 * @tparam Formatter
	 * 		Formatter type.
	 * 
	 * @tparam Stream
	 * 		Stream type.
	 *
	 * @tparam Pattern
	 * 		Pattern type.
	 * 
	 * @tparam Arguments
	 * 		Arguments types.
	 * 
	 * @param[inout] stream
	 * 		Stream to which the formatted string will be passed.
	 * 
	 * @param[in] pattern
	 * 		Pattern by which string and arguments will be formatted.
	 * 
	 * @param[in] arguments
	 * 		Format arguments / variables.
	 */
	template<typename Formatter = BasicArgumentsFormatter<char>, typename Pattern, typename Stream, typename... Arguments>
	FMATIO_INLINE void cecho(Stream& stream, const Pattern& pattern, Arguments&&... arguments) FMATIO_NOEXCEPT;

	/**
	 * Echo formatted string of wide chars by format function.
	 * 
	 * @tparam Formatter
	 * 		Formatter type.
	 * 
	 * @tparam Stream
	 * 		Stream type.
	 *
	 * @tparam Pattern
	 * 		Pattern type.
	 * 
	 * @tparam Arguments
	 * 		Arguments types.
	 * 
	 * @param[inout] stream
	 * 		Stream to which the formatted string will be passed.
	 * 
	 * @param[in] pattern
	 * 		Pattern by which string and arguments will be formatted.
	 * 
	 * @param[in] arguments
	 * 		Format arguments / variables.
	 */
	template<typename Formatter = BasicArgumentsFormatter<wchar>, typename Pattern, typename Stream, typename... Arguments>
	FMATIO_INLINE void wecho(Stream& stream, const Pattern& pattern, Arguments&&... arguments) FMATIO_NOEXCEPT;
}

#include "./format.inl"

#endif
