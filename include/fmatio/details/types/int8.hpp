/*******************************************************************************
 * @file int8.hpp
 *
 * @author Joris Baranauskas (jorisb)
 *
 * Defines functions to write signed 8-bit integer.
 *
 * @copyright © 2022-2023 by Joris Baranauskas
 *
 * This file is distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.
 * You should have received a copy of the license along with this project.
 * If not, see https://www.gnu.org/licenses/.
 ******************************************************************************/

#ifndef FMATIO_INCLUDE_FMATIO_DETAILS_TYPES_INT8_HPP
#define FMATIO_INCLUDE_FMATIO_DETAILS_TYPES_INT8_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#	pragma once
#endif

#include <fmatio/core.hpp>
#include <fmatio/types.hpp>

#include <fmatio/details/writers.hpp>

#include <string>

namespace fmatio
{
	namespace details
	{
		template<typename Char>
		FMATIO_INLINE void int8Handle(BasicFormatWriter<Char>& writer, int8 value) FMATIO_NOEXCEPT
		{
			::std::string string = ::std::to_string(value);	// Have to reimplement this!
			writer.write(BasicStringView<Char>(string.data()));
		}
	}
}

#endif
