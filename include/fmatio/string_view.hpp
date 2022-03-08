/*******************************************************************************
 * @file string_view.hpp
 * 
 * @author Joris Baranauskas (jorisb)
 * 
 * Defines string view class.
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
	class BasicStringView
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
		
		/**
		 * Define a public typedef for value type used in this class.
		 */
		using ValueType = Char;

	private:
		const Char* data;
		uint32 size;

	public:
		BasicStringView<Char>() noexcept;

		BasicStringView<Char>(const Char* data) noexcept;

		BasicStringView<Char>(const BasicStringView<Char>& other) noexcept = default;

#if defined(FMATIO_MOVE_SEMANTICS_ENABLED) && FMATIO_MOVE_SEMANTICS_ENABLED == 1
		BasicStringView<Char>(BasicStringView<Char>&& other) noexcept = default;
#endif

		~BasicStringView<Char>() noexcept;

	public:
		const Char* getData() const noexcept;

		uint32 getSize() const noexcept;

		bool isEmpty() const noexcept;

		const Char* getBegin() const noexcept;
		
		const Char* getEnd() const noexcept;

	public:
		BasicStringView<Char>& operator =(const BasicStringView<Char>& other) noexcept = default;

#if defined(FMATIO_MOVE_SEMANTICS_ENABLED) && FMATIO_MOVE_SEMANTICS_ENABLED == 1
		BasicStringView<Char>& operator =(BasicStringView<Char>&& other) noexcept = default;
#endif

		bool operator ==(const BasicStringView<Char>& other) const noexcept;

		bool operator !=(const BasicStringView<Char>& other) const noexcept;

		const Char& operator [](uint32 index) const noexcept;
	};
}

#include "./string_view.inl"

#endif
