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
	template<typename Formatter, typename Char>
	FMATIO_INLINE void formatHandle(details::BasicFormatWriter<Char>& writer, BasicStringView<Char> pattern, const details::BasicFormatArgumentsList<Char>& arguments) FMATIO_NOEXCEPT
	{
		Formatter formatter;
		formatter.format(writer, pattern, arguments);
	}

	template<typename Formatter, typename Result, typename Pattern, typename... Arguments>
	FMATIO_INLINE Result format(const Pattern& pattern, Arguments&&... arguments) FMATIO_NOEXCEPT
	{
		using CharType = typename Result::CharType; Result result = Result();
		details::BasicDynamicWriter<Result> writer = details::BasicDynamicWriter<Result>(result);
		formatHandle<Formatter, CharType>(writer, BasicStringView<CharType>(pattern), { details::makeFormatArgument<CharType, details::Formattable<Arguments>>(arguments)... });
		FMATIO_ASSERT(result.getData() != nullptr && result.getSize() > 0, "Format resulted in a invalid string!");
		return result;
	}

	template<typename Formatter = SafeIteratorFormatter<char>, typename Pattern, typename... Arguments>
	FMATIO_INLINE BasicString<char> cformat(const Pattern& pattern, Arguments&&... arguments) FMATIO_NOEXCEPT
	{
		BasicString<char> result = format<Formatter, BasicString<char>, Pattern, Arguments...>(pattern, ::std::forward<Arguments>(arguments)...);
		return result;
	}

	template<typename Formatter = SafeIteratorFormatter<wchar>, typename Pattern, typename... Arguments>
	FMATIO_INLINE BasicString<wchar> wformat(const Pattern& pattern, Arguments&&... arguments) FMATIO_NOEXCEPT
	{
		BasicString<wchar> result = format<Formatter, BasicString<wchar>, Pattern, Arguments...>(pattern, ::std::forward<Arguments>(arguments)...);
		return result;
	}

	template<typename Formatter, typename Result, typename Stream, typename Pattern, typename... Arguments>
	FMATIO_INLINE void echo(Stream& stream, const Pattern& pattern, Arguments&&... arguments) FMATIO_NOEXCEPT
	{
		Result result = format<Formatter, Result, Pattern, Arguments...>(pattern, ::std::forward<Arguments>(arguments)...);
		stream << result.getData();
	}

	template<typename Formatter = SafeIteratorFormatter<char>, typename Pattern, typename Stream, typename... Arguments>
	FMATIO_INLINE void cecho(Stream& stream, const Pattern& pattern, Arguments&&... arguments) FMATIO_NOEXCEPT
	{
		BasicString<char> result = cformat<Formatter, Pattern, Arguments...>(pattern, ::std::forward<Arguments>(arguments)...);
		stream << result.getData();
	}

	template<typename Formatter = SafeIteratorFormatter<wchar>, typename Pattern, typename Stream, typename... Arguments>
	FMATIO_INLINE void wecho(Stream& stream, const Pattern& pattern, Arguments&&... arguments) FMATIO_NOEXCEPT
	{
		BasicString<wchar> result = wformat<Formatter, Pattern, Arguments...>(pattern, ::std::forward<Arguments>(arguments)...);
		stream << result.getData();
	}
}
