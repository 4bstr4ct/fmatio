/*******************************************************************************
 * @file string.hpp
 * 
 * @author Joris Baranauskas (jorisb)
 * 
 * Defines macros and helper utilities.
 * 
 * @copyright © 2022-2023 by Joris Baranauskas
 * 
 * This file are distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.
 * You should have received a copy of the license along with this project.
 * If not, see https://www.gnu.org/licenses/.
 ******************************************************************************/

#ifndef FMATIO_INCLUDE_FMATIO_STRING_HPP
#define FMATIO_INCLUDE_FMATIO_STRING_HPP

#include <fmatio/core.hpp>
#include <fmatio/types.hpp>

namespace fmatio
{
	template<typename Char>
	class BasicString
	{
	public:
		/**
		 * Define a const iterator to iterate through the data.
		 */
		using Iterator = const Char*;

		/**
		 * Define a public typedef for char type used in this class.
		 */
		using CharType = Char;

	private:
		Char* data;
		uint32 size;
	};

	/**
	 * Define a string with char as the inner type.
	 */
	using String = BasicString<char>;
}

#endif
