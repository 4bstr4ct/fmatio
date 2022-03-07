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
 * This file are distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.
 * You should have received a copy of the license along with this project.
 * If not, see https://www.gnu.org/licenses/.
 ******************************************************************************/

#ifndef FMATIO_INCLUDE_FMATIO_FORMAT_HPP
#define FMATIO_INCLUDE_FMATIO_FORMAT_HPP

#include <fmatio/core.hpp>
#include <fmatio/types.hpp>
#include <fmatio/writers.hpp>
#include <fmatio/string_view.hpp>
#include <fmatio/details/arguments.hpp>

#include <string>

namespace fmatio
{
	template<typename Char>
	FMATIO_API void formatImpl(BasicFormatWriter<Char>& writer, BasicStringView<Char> pattern, const BasicFormatArgumentsList<Char>& arguments) noexcept
	{
		uint32 index = 0;

		for (BasicStringView<Char>::Iterator it = pattern.getBegin(); it != pattern.getEnd(); it++)
		{
			if (*it == '{' && *(it + 1) == '}')
			{
				arguments.formatArgument(writer, index++); it++;
			}
			else
			{
				Char letter[2] = { *it, '\0' };
				writer.write(BasicStringView<Char>(letter));
			}
		}
	}

	template<typename T>
	using DecayArray = ::std::conditional_t<::std::is_array_v<T>, ::std::remove_extent_t<T> const*, T>;

	template<typename T>
	using Formattable = DecayArray<::std::remove_reference_t<T>>;

	template<typename Result, typename Pattern, typename... Arguments>
	FMATIO_API Result format(const Pattern& pattern, const Arguments&... arguments) noexcept
	{
		using CharType = Result::CharType;
		Result result;
		BasicDynamicWriter<Result> writer(result);
		formatImpl(writer, BasicStringView<CharType>(pattern), { makeFormatArgument<CharType, Formattable<Arguments>>(arguments)... });
		return result;
	}
}

#include "../source/fmatio/format.inl"

#endif
