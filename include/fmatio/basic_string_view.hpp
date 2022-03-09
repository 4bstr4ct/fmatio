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
		BasicStringView() noexcept;

		BasicStringView(const Char* data) noexcept;

		BasicStringView(const Char* data, uint32 size) noexcept;

		BasicStringView(const BasicStringView& other) noexcept = default;

#if defined(FMATIO_MOVE_SEMANTICS_ENABLED) && FMATIO_MOVE_SEMANTICS_ENABLED == 1
		BasicStringView(BasicStringView&& other) noexcept = default;
#endif

		~BasicStringView() noexcept;

	public:
		const Char* getData() const noexcept;

		uint32 getSize() const noexcept;

		bool isEmpty() const noexcept;

		const Char* getConstBegin() const noexcept;
		
		const Char* getConstEnd() const noexcept;

	public:
		BasicStringView<Char>& operator =(const BasicStringView& other) noexcept = default;

#if defined(FMATIO_MOVE_SEMANTICS_ENABLED) && FMATIO_MOVE_SEMANTICS_ENABLED == 1
		BasicStringView<Char>& operator =(BasicStringView&& other) noexcept = default;
#endif

		bool operator ==(const BasicStringView& other) const noexcept;

		bool operator !=(const BasicStringView& other) const noexcept;

		const Char& operator [](uint32 index) const noexcept;
	};
}

#include "./basic_string_view.inl"

#endif
