/*******************************************************************************
 * @file char_string.hpp
 *
 * @author Joris Baranauskas (jorisb)
 *
 * Defines functions to write char string.
 *
 * @copyright © 2022-2023 by Joris Baranauskas
 *
 * This file is distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.
 * You should have received a copy of the license along with this project.
 * If not, see https://www.gnu.org/licenses/.
 ******************************************************************************/

#ifndef FMATIO_INCLUDE_FMATIO_DETAILS_TYPES_CHAR_STRING_HPP
#define FMATIO_INCLUDE_FMATIO_DETAILS_TYPES_CHAR_STRING_HPP

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
		FMATIO_INLINE void charStringHandle(BasicFormatWriter<Char>& writer, char* value) FMATIO_NOEXCEPT
		{
			writer.write(BasicStringView<Char>(value));
		}

		template<typename Char>
		FMATIO_INLINE void charStringHandle(BasicFormatWriter<Char>& writer, const char* value) FMATIO_NOEXCEPT
		{
			writer.write(BasicStringView<Char>(value));
		}
	}
}

#endif
