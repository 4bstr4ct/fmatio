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

namespace fmatio
{
	template<typename Char, typename Formatter>
	FMATIO_INLINE void formatHandle(details::BasicFormatWriter<Char>& writer, BasicStringView<Char> pattern, const details::BasicFormatArgumentsList<Char>& arguments) FMATIO_NOEXCEPT
	{
		Formatter formatter;
		formatter.format(writer, pattern, arguments);
	}

	template<typename Char, typename Formatter, typename Result, typename Pattern, typename... Arguments>
	FMATIO_INLINE Result format(const Pattern& pattern, Arguments&&... arguments) FMATIO_NOEXCEPT
	{
		using CharType = typename Char; Result result = Result();
		details::BasicDynamicWriter<Result> writer = details::BasicDynamicWriter<Result>(result);
		formatHandle<CharType, Formatter>(writer, BasicStringView<CharType>(pattern), { details::makeFormatArgument<CharType, details::Formattable<Arguments>>(arguments)... });
		FMATIO_ASSERT(result.getData() != nullptr && result.getSize() > 0, "Format resulted in a invalid string!");
		return result;
	}

	template<typename Char, typename Formatter, typename Result, typename Pattern, typename... Arguments>
	FMATIO_INLINE Result cformat(const Pattern& pattern, Arguments&&... arguments) FMATIO_NOEXCEPT
	{
		Result result = format<Char, Formatter, Result, Pattern, Arguments...>(pattern, details::forward<Arguments>(arguments)...);
		return result;
	}

	template<typename Char, typename Formatter, typename Result, typename Pattern, typename... Arguments>
	FMATIO_INLINE Result wformat(const Pattern& pattern, Arguments&&... arguments) FMATIO_NOEXCEPT
	{
		Result result = format<Char, Formatter, Result, Pattern, Arguments...>(pattern, details::forward<Arguments>(arguments)...);
		return result;
	}

	template<typename Char, typename Formatter, typename Result, typename Stream, typename Pattern, typename... Arguments>
	FMATIO_INLINE void echo(Stream& stream, const Pattern& pattern, Arguments&&... arguments) FMATIO_NOEXCEPT
	{
		Result result = format<Char, Formatter, Result, Pattern, Arguments...>(pattern, details::forward<Arguments>(arguments)...);
		stream << result.getData();
	}

	template<typename Char, typename Formatter, typename Result, typename Stream, typename Pattern, typename... Arguments>
	FMATIO_INLINE void cecho(Stream& stream, const Pattern& pattern, Arguments&&... arguments) FMATIO_NOEXCEPT
	{
		Result result = format<Char, Formatter, Result, Pattern, Arguments...>(pattern, details::forward<Arguments>(arguments)...);
		stream << result.getData();
	}

	template<typename Char, typename Formatter, typename Result, typename Stream, typename Pattern, typename... Arguments>
	FMATIO_INLINE void wecho(Stream& stream, const Pattern& pattern, Arguments&&... arguments) FMATIO_NOEXCEPT
	{
		Result result = format<Char, Formatter, Result, Pattern, Arguments...>(pattern, details::forward<Arguments>(arguments)...);
		stream << result.getData();
	}
}
