/*******************************************************************************
 * @file format.inl
 * 
 * @author Joris Baranauskas (jorisb)
 * 
 * Defines format.hpp implementations.
 * 
 * @copyright © 2022-2023 by Joris Baranauskas
 * 
 * This file are distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.
 * You should have received a copy of the license along with this project.
 * If not, see https://www.gnu.org/licenses/.
 ******************************************************************************/

namespace fmatio
{
	template<typename Char>
	void formatHandle(details::BasicFormatWriter<Char>& writer, BasicStringView<Char> pattern, const details::BasicFormatArgumentsList<Char>& arguments) noexcept
	{
		uint32 count = 0;

		for (BasicStringView<Char>::Iterator it = pattern.getBegin(); it != pattern.getEnd(); it++)
			if (*it == '{' && *(it + 1) == '}')
				count++;

		FMATIO_ASSERT(count == arguments.getSize(), "Format arguments count and their placeholders \'{}\' count are different!");

		uint32 index = 0;

		for (BasicStringView<Char>::Iterator it = pattern.getBegin(); it != pattern.getEnd(); it++)
		{
			if (*it == '{' && *(it + 1) == '}')
			{
				arguments.format(writer, index++); it++;
			}
			else
			{
				Char letter[2] = { *it, '\0' };
				writer.write(BasicStringView<Char>(letter));
			}
		}
	}

	template<typename Result, typename Pattern, typename... Arguments>
	Result format(const Pattern& pattern, Arguments&&... arguments) noexcept
	{
		using CharType = Result::CharType; Result result;
		details::BasicDynamicWriter<Result> writer = details::BasicDynamicWriter<Result>(result);
		formatHandle(writer, BasicStringView<CharType>(pattern), { details::makeFormatArgument<CharType>(arguments)... });
		return result;
	}

	template<typename Pattern, typename... Arguments>
	BasicString<char> format(const Pattern& pattern, Arguments&&... arguments) noexcept
	{
		BasicString<char> result = format<BasicString<char>, Pattern, Arguments...>(pattern, ::std::forward<Arguments>(arguments)...);
		return result;
	}

	template<typename Pattern, typename... Arguments>
	BasicString<wchar> wformat(const Pattern& pattern, Arguments&&... arguments) noexcept
	{
		BasicString<wchar> result = format<BasicString<wchar>, Pattern, Arguments...>(pattern, ::std::forward<Arguments>(arguments)...);
		return result;
	}

	template<typename Stream, typename Pattern, typename... Arguments>
	void echo(Stream& stream, const Pattern& pattern, Arguments&&... arguments) noexcept
	{
		stream << format<Pattern, Arguments...>(pattern, ::std::forward<Arguments>(arguments)...).getData();
	}

	template<typename Stream, typename Pattern, typename... Arguments>
	void wecho(Stream& stream, const Pattern& pattern, Arguments&&... arguments) noexcept
	{
		stream << format<Pattern, Arguments...>(pattern, ::std::forward<Arguments>(arguments)...).getData();
	}
}
