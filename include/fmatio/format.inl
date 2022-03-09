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

		for (BasicStringView<Char>::ConstIterator it = pattern.getConstBegin(); it != pattern.getConstEnd(); it++)
			if (*it == '{' && *(it + 1) == '}')
				count++;

		FMATIO_ASSERT(count == arguments.getSize(), "Format arguments count and their placeholders \'{}\' count are different!");
		uint32 index = 0;

		for (BasicStringView<Char>::ConstIterator it = pattern.getConstBegin(); it != pattern.getConstEnd(); it++)
		{
			if (*it == '{' && *(it + 1) == '}' && index <= pattern.getSize())
			{
				arguments.format(writer, index++); it++;
			}
			else
			{
				writer.write(BasicStringView<Char>(it, 1));
			}
		}

		writer.write(BasicStringView<Char>((char*)"\0", 1));
	}

	template<typename Result, typename Pattern, typename... Arguments>
	Result format(const Pattern& pattern, Arguments&&... arguments) noexcept
	{
		using CharType = Result::CharType; Result result = Result();
		details::BasicDynamicWriter<Result> writer = details::BasicDynamicWriter<Result>(result);
		formatHandle(writer, BasicStringView<CharType>(pattern), { details::makeFormatArgument<CharType>(arguments)... });
		FMATIO_ASSERT(result.getData() != nullptr && result.getSize() > 0, "Format resulted in a invalid string!");
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
}
