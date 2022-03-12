/*******************************************************************************
 * @file formatters.inl
 * 
 * @author Joris Baranauskas (jorisb)
 * 
 * Defines various formatters.
 * 
 * @copyright © 2022-2023 by Joris Baranauskas
 * 
 * This file is distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.
 * You should have received a copy of the license along with this project.
 * If not, see https://www.gnu.org/licenses/.
 ******************************************************************************/

#include <fmatio/types.hpp>

#include <fmatio/details/format_traits.hpp>

namespace fmatio
{
	template<typename Char>
	void SafeIteratorFormatter<Char>::format(details::BasicFormatWriter<Char>& writer, BasicStringView<Char> pattern, const details::BasicFormatArgumentsList<Char>& arguments) FMATIO_NOEXCEPT
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
}
