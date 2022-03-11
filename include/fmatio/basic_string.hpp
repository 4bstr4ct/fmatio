/*******************************************************************************
 * @file basic_string.hpp
 * 
 * @author Joris Baranauskas (jorisb)
 * 
 * Defines basic string class.
 * 
 * @copyright © 2022-2023 by Joris Baranauskas
 * 
 * This file is distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.
 * You should have received a copy of the license along with this project.
 * If not, see https://www.gnu.org/licenses/.
 ******************************************************************************/

#ifndef FMATIO_INCLUDE_FMATIO_BASIC_STRING_HPP
#define FMATIO_INCLUDE_FMATIO_BASIC_STRING_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#	pragma once
#endif

#include <fmatio/core.hpp>
#include <fmatio/types.hpp>

namespace fmatio
{
	template<typename Char>
	class BasicString
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
		uint32 capacity;

	public:
		BasicString() FMATIO_NOEXCEPT;

		BasicString(uint32 capacity) FMATIO_NOEXCEPT;

		BasicString(const Char* const data) FMATIO_NOEXCEPT;

		BasicString(const BasicString& other) FMATIO_NOEXCEPT;

#if defined(FMATIO_MOVE_SEMANTICS_ENABLED) && FMATIO_MOVE_SEMANTICS_ENABLED == 1
		BasicString(BasicString&& other) FMATIO_NOEXCEPT;
#endif

		~BasicString() FMATIO_NOEXCEPT;

	private:
		void initialize(uint32 capacity) FMATIO_NOEXCEPT;

		void reallocate(uint32 newCapacity) FMATIO_NOEXCEPT;

		void copy(const Char* const data, uint32 size) FMATIO_NOEXCEPT;

		void deallocate() FMATIO_NOEXCEPT;

	public:
		const Char* getData() const FMATIO_NOEXCEPT;

		uint32 getSize() const FMATIO_NOEXCEPT;

		uint32 getCapacity() const FMATIO_NOEXCEPT;

		bool isEmpty() const FMATIO_NOEXCEPT;

		void append(const Char* const string) FMATIO_NOEXCEPT;

		void append(const Char* const begin, uint32 size) FMATIO_NOEXCEPT;

		void clear() FMATIO_NOEXCEPT;

		Char* getBegin() FMATIO_NOEXCEPT;
		
		Char* getEnd() FMATIO_NOEXCEPT;

		const Char* getConstBegin() const FMATIO_NOEXCEPT;
		
		const Char* getConstEnd() const FMATIO_NOEXCEPT;

	public:
		BasicString& operator =(const BasicString& other) FMATIO_NOEXCEPT;

#if defined(FMATIO_MOVE_SEMANTICS_ENABLED) && FMATIO_MOVE_SEMANTICS_ENABLED == 1
		BasicString& operator =(BasicString&& other) FMATIO_NOEXCEPT;
#endif

		bool operator ==(const BasicString& other) const FMATIO_NOEXCEPT;

		bool operator !=(const BasicString& other) const FMATIO_NOEXCEPT;

		Char& operator [](uint32 index) FMATIO_NOEXCEPT;

		const Char& operator [](uint32 index) const FMATIO_NOEXCEPT;
	};
}

#include "./basic_string.inl"

#endif
