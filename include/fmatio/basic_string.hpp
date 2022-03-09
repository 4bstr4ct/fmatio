/*******************************************************************************
 * @file basic_string.hpp
 * 
 * @author Joris Baranauskas (jorisb)
 * 
 * Defines basic string class.
 * 
 * @copyright © 2022-2023 by Joris Baranauskas
 * 
 * This file are distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.
 * You should have received a copy of the license along with this project.
 * If not, see https://www.gnu.org/licenses/.
 ******************************************************************************/

#ifndef FMATIO_INCLUDE_FMATIO_BASIC_STRING_HPP
#define FMATIO_INCLUDE_FMATIO_BASIC_STRING_HPP

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
		BasicString() noexcept;

		BasicString(uint32 capacity) noexcept;

		BasicString(const Char* const data) noexcept;

		BasicString(const BasicString& other) noexcept;

#if defined(FMATIO_MOVE_SEMANTICS_ENABLED) && FMATIO_MOVE_SEMANTICS_ENABLED == 1
		BasicString(BasicString&& other) noexcept;
#endif

		~BasicString() noexcept;

	private:
		void initialize(uint32 capacity) noexcept;

		void reallocate(uint32 newCapacity) noexcept;

		void copy(const Char* const data, uint32 size) noexcept;

		void deallocate() noexcept;

	public:
		const Char* getData() const noexcept;

		uint32 getSize() const noexcept;

		uint32 getCapacity() const noexcept;

		bool isEmpty() const noexcept;

		void append(const Char* const string) noexcept;

		void append(const Char* const begin, uint32 size) noexcept;

		void clear() noexcept;

		Char* getBegin() noexcept;
		
		Char* getEnd() noexcept;

		const Char* getConstBegin() const noexcept;
		
		const Char* getConstEnd() const noexcept;

	public:
		BasicString& operator =(const BasicString& other) noexcept;

#if defined(FMATIO_MOVE_SEMANTICS_ENABLED) && FMATIO_MOVE_SEMANTICS_ENABLED == 1
		BasicString& operator =(BasicString&& other) noexcept;
#endif

		bool operator ==(const BasicString& other) const noexcept;

		bool operator !=(const BasicString& other) const noexcept;

		Char& operator [](uint32 index) noexcept;

		const Char& operator [](uint32 index) const noexcept;
	};
}

#include "./basic_string.inl"

#endif
