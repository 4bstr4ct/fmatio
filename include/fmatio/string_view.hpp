/*******************************************************************************
 * @file string_view.hpp
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

#ifndef FMATIO_INCLUDE_FMATIO_STRING_VIEW_HPP
#define FMATIO_INCLUDE_FMATIO_STRING_VIEW_HPP

#include <fmatio/core.hpp>
#include <fmatio/types.hpp>

namespace fmatio
{
	template<typename Char>
	FMATIO_API class BasicStringView
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
		const Char* data;
		uint32 size;

	public:
		BasicStringView<Char>();

		BasicStringView<Char>(const Char* data);

		BasicStringView<Char>(const BasicStringView<Char>& other) = default;

#if defined(FMATIO_MOVE_SEMANTICS_ENABLED) && FMATIO_MOVE_SEMANTICS_ENABLED == 1
		BasicStringView<Char>(BasicStringView<Char>&& other) = delete;
#endif

		~BasicStringView<Char>();

	public:
		const Char* getData() const;

		uint32 getSize() const;

		bool isEmpty() const;

		const Char* getBegin() const;
		
		const Char* getEnd() const;

	public:
		BasicStringView<Char>& operator =(const BasicStringView<Char>& other) = default;

#if defined(FMATIO_MOVE_SEMANTICS_ENABLED) && FMATIO_MOVE_SEMANTICS_ENABLED == 1
		BasicStringView<Char>& operator =(BasicStringView<Char>&& other) = delete;
#endif

		bool operator ==(const BasicStringView<Char>& other) const;

		bool operator !=(const BasicStringView<Char>& other) const;

		Char& operator [](uint32 index);

		const Char& operator [](uint32 index) const;
	};

	/**
	 * Define a string view with char as the inner type.
	 */
	using StringView = BasicStringView<char>;
}

#include "../../source/fmatio/string_view.inl"

#endif
