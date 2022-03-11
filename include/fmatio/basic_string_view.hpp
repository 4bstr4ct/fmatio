/*******************************************************************************
 * @file basic_string_view.hpp
 * 
 * @author Joris Baranauskas (jorisb)
 * 
 * Defines basic string view class.
 * 
 * @copyright © 2022-2023 by Joris Baranauskas
 * 
 * This file is distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.
 * You should have received a copy of the license along with this project.
 * If not, see https://www.gnu.org/licenses/.
 ******************************************************************************/

#ifndef FMATIO_INCLUDE_FMATIO_BASIC_STRING_VIEW_HPP
#define FMATIO_INCLUDE_FMATIO_BASIC_STRING_VIEW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#	pragma once
#endif

#include <fmatio/core.hpp>
#include <fmatio/types.hpp>

namespace fmatio
{
	template<typename Char>
	class BasicStringView
	{
	public:
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
		const Char* data;
		uint32 size;

	public:
		BasicStringView() FMATIO_NOEXCEPT;

		BasicStringView(const Char* data) FMATIO_NOEXCEPT;

		BasicStringView(const Char* data, uint32 size) FMATIO_NOEXCEPT;

		BasicStringView(const BasicStringView& other) FMATIO_NOEXCEPT = default;

#if defined(FMATIO_MOVE_SEMANTICS_ENABLED) && FMATIO_MOVE_SEMANTICS_ENABLED == 1
		BasicStringView(BasicStringView&& other) FMATIO_NOEXCEPT = default;
#endif

		~BasicStringView() FMATIO_NOEXCEPT;

	public:
		const Char* getData() const FMATIO_NOEXCEPT;

		uint32 getSize() const FMATIO_NOEXCEPT;

		bool isEmpty() const FMATIO_NOEXCEPT;

		const Char* getConstBegin() const FMATIO_NOEXCEPT;
		
		const Char* getConstEnd() const FMATIO_NOEXCEPT;

	public:
		BasicStringView<Char>& operator =(const BasicStringView& other) FMATIO_NOEXCEPT = default;

#if defined(FMATIO_MOVE_SEMANTICS_ENABLED) && FMATIO_MOVE_SEMANTICS_ENABLED == 1
		BasicStringView<Char>& operator =(BasicStringView&& other) FMATIO_NOEXCEPT = default;
#endif

		bool operator ==(const BasicStringView& other) const FMATIO_NOEXCEPT;

		bool operator !=(const BasicStringView& other) const FMATIO_NOEXCEPT;

		const Char& operator [](uint32 index) const FMATIO_NOEXCEPT;
	};
}

#include "./basic_string_view.inl"

#endif
