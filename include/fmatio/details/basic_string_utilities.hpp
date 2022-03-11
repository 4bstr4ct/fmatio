/*******************************************************************************
 * @file basic_string_utilities.hpp
 *
 * @author Joris Baranauskas (jorisb)
 *
 * Defines classes and utilitites for format traits.
 *
 * @copyright © 2022-2023 by Joris Baranauskas
 *
 * This file is distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.
 * You should have received a copy of the license along with this project.
 * If not, see https://www.gnu.org/licenses/.
 ******************************************************************************/

#ifndef FMATIO_INCLUDE_FMATIO_DETAILS_BASIC_STRING_UTILITIES_HPP
#define FMATIO_INCLUDE_FMATIO_DETAILS_BASIC_STRING_UTILITIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#	pragma once
#endif

#include <fmatio/core.hpp>
#include <fmatio/types.hpp>

namespace fmatio
{
	namespace details
	{
		template<typename Char>
		FMATIO_CONSTEXPR FMATIO_INLINE uint32 stringSize(const Char* const string) FMATIO_NOEXCEPT
		{
			const Char *iterator;
			for (iterator = string; *iterator; ++iterator);
			return (uint32)(iterator - string);
		}

		template<typename Char>
		FMATIO_CONSTEXPR FMATIO_INLINE void stringCopy(Char* destination, const Char* const source, uint32 size) FMATIO_NOEXCEPT
		{
			Char* destinationIterator = destination;
			const Char* sourceIterator = source;
			while (size--) *destinationIterator++ = *sourceIterator++;
		}
	}
}

#endif
