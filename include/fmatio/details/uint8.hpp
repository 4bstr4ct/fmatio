/*******************************************************************************
 * @file uint8.hpp
 *
 * @author Joris Baranauskas (jorisb)
 *
 * Defines functions to write unsigned 8-bit integer.
 *
 * @copyright © 2022-2023 by Joris Baranauskas
 *
 * This file is distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.
 * You should have received a copy of the license along with this project.
 * If not, see https://www.gnu.org/licenses/.
 ******************************************************************************/

#ifndef FMATIO_INCLUDE_FMATIO_DETAILS_UINT8_HPP
#define FMATIO_INCLUDE_FMATIO_DETAILS_UINT8_HPP

#include <fmatio/core.hpp>
#include <fmatio/types.hpp>

#include <fmatio/details/writers.hpp>

#include <string>

namespace fmatio
{
	namespace details
	{
		template<typename Char>
		void uint8Handle(BasicFormatWriter<Char>& writer, uint8 value) noexcept
		{
			::std::string string = ::std::to_string(value);	// Have to reimplement this!
			writer.write(BasicStringView<Char>(string.data()));
		}
	}
}

#endif
