/*******************************************************************************
 * @file format.inl
 * 
 * @author Joris Baranauskas (jorisb)
 * 
 * Defines format.hpp implementations.
 * 
 * @copyright © 2022-2023 by Joris Baranauskas
 * 
 * This file is distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.
 * You should have received a copy of the license along with this project.
 * If not, see https://www.gnu.org/licenses/.
 ******************************************************************************/

#include <fmatio/details/format_traits.hpp>

namespace fmatio
{
	template<typename Char>
	FMATIO_INLINE void formatHandle(details::BasicFormatWriter<Char>& writer, BasicStringView<Char> pattern, const details::BasicFormatArgumentsList<Char>& arguments) FMATIO_NOEXCEPT
	{
		uint32 count = 0;

		for (typename BasicStringView<Char>::ConstIterator it = pattern.getConstBegin(); it != pattern.getConstEnd(); it++)
			if (*it == details::FormatTraits<Char>::formatBegin && *(it + 1) == details::FormatTraits<Char>::formatEnd)
				count++;

		FMATIO_ASSERT(count == arguments.getSize(), "Format arguments count and their placeholders \'{}\' count are different!");
		uint32 index = 0;

		for (typename BasicStringView<Char>::ConstIterator it = pattern.getConstBegin(); it != pattern.getConstEnd(); it++)
		{
			if (*it == details::FormatTraits<Char>::formatBegin && *(it + 1) == details::FormatTraits<Char>::formatEnd && index <= pattern.getSize())
			{
				arguments.format(writer, index++); it++;
			}
			else
			{
				writer.write(BasicStringView<Char>(it, 1));
			}
		}

		writer.write(BasicStringView<Char>((Char*)"\0", 1));
	}

	template<typename Result, typename Pattern, typename... Arguments>
	FMATIO_INLINE Result format(const Pattern& pattern, Arguments&&... arguments) FMATIO_NOEXCEPT
	{
		using CharType = typename Result::CharType; Result result = Result();
		details::BasicDynamicWriter<Result> writer = details::BasicDynamicWriter<Result>(result);
		formatHandle(writer, BasicStringView<CharType>(pattern), { details::makeFormatArgument<CharType, details::Formattable<Arguments>>(arguments)... });
		FMATIO_ASSERT(result.getData() != nullptr && result.getSize() > 0, "Format resulted in a invalid string!");
		return result;
	}

	template<typename Pattern, typename... Arguments>
	FMATIO_INLINE BasicString<char> format(const Pattern& pattern, Arguments&&... arguments) FMATIO_NOEXCEPT
	{
		BasicString<char> result = format<BasicString<char>, Pattern, Arguments...>(pattern, ::std::forward<Arguments>(arguments)...);
		return result;
	}

	template<typename Pattern, typename... Arguments>
	FMATIO_INLINE BasicString<wchar> wformat(const Pattern& pattern, Arguments&&... arguments) FMATIO_NOEXCEPT
	{
		BasicString<wchar> result = format<BasicString<wchar>, Pattern, Arguments...>(pattern, ::std::forward<Arguments>(arguments)...);
		return result;
	}

	template<typename Stream, typename Pattern, typename... Arguments>
	FMATIO_INLINE void echo(Stream& stream, const Pattern& pattern, Arguments&&... arguments) FMATIO_NOEXCEPT
	{
		BasicString<char> string = format<Pattern, Arguments...>(pattern, ::std::forward<Arguments>(arguments)...);
		stream << string.getData();
	}
}
