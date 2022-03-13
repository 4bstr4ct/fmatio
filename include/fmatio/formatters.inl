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
	ArgumentsFormatterBase<Char>::~ArgumentsFormatterBase() { }

	template<typename Char>
	BasicArgumentsFormatter<Char>::~BasicArgumentsFormatter() { }
	
	template<typename Char>
	void BasicArgumentsFormatter<Char>::format(details::BasicFormatWriter<Char>& writer, BasicStringView<Char> pattern, const details::BasicFormatArgumentsList<Char>& arguments) FMATIO_NOEXCEPT
	{
		bool enableFormatting = false;
		typename BasicStringView<Char>::ConstIterator iterator = pattern.getConstBegin();
		typename BasicStringView<Char>::ConstIterator previous = iterator;

		for (uint32 index = 0; iterator != pattern.getConstEnd(); iterator++)
		{
			if (*iterator == details::FormatTraits<Char>::formatBegin)
			{
				writer.write(BasicStringView<Char>(previous, (uint32)(iterator - previous)));
				enableFormatting = true;
			}
			else if (*iterator == details::FormatTraits<Char>::formatEnd && enableFormatting)
			{
				previous = iterator + 1;
				arguments[index++].format(writer);
				enableFormatting = false;
			}
		}

		iterator++;
		writer.write(BasicStringView<Char>(previous, (uint32)(iterator - previous)));
	}
}
