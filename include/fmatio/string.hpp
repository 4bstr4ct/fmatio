/*******************************************************************************
 * @file string.hpp
 * 
 * @author Joris Baranauskas (jorisb)
 * 
 * Defines string class.
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
	FMATIO_API class BasicString
	{
	public:
		/**
		 * Define a iterator to iterate through the data.
		 */
		using Iterator = Char*;

		/**
		 * Define a const iterator to iterate through the data.
		 */
		using ConstIterator = const Char*;

		/**
		 * Define a public typedef for char type used in this class.
		 */
		using CharType = Char;
		
		/**
		 * Define a public typedef for value type used in this class.
		 */
		using ValueType = Char;

	private:
		Char* data;
		uint32 size;

	public:
		Char* getData() noexcept
		{
			return this->data;
		}

		const Char* getData() const noexcept
		{
			return this->data;
		}

		uint32 getSize() const noexcept
		{
			return this->size;
		}

		void append(const Char* begin, uint32 size) noexcept
		{
		}
	};
}

#endif
