/*******************************************************************************
 * @file arguments.hpp
 *
 * @author Joris Baranauskas (jorisb)
 *
 * Defines classes and utilitites for formatting arguments.
 *
 * @copyright © 2022-2023 by Joris Baranauskas
 *
 * This file are distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.
 * You should have received a copy of the license along with this project.
 * If not, see https://www.gnu.org/licenses/.
 ******************************************************************************/

#ifndef FMATIO_INCLUDE_FMATIO_DETAILS_ARGUMENTS_HPP
#define FMATIO_INCLUDE_FMATIO_DETAILS_ARGUMENTS_HPP

#include <fmatio/core.hpp>
#include <fmatio/types.hpp>

namespace fmatio
{
	enum class FormatArgumentType : uint8
	{
		Unknown,
		Char,
		WChar,
		SignedChar,
		UnsignedChar,
		SignedInt,
		UnsignedInt,
		SignedShortInt,
		UnsignedShortInt,
		SignedLongInt,
		UnsignedLongInt,
		SignedLongLongInt,
		UnsignedLongLongInt,
		SingleFloat,
		DoubleFloat,
		Boolean,
		CharString,
		WCharString,
		NullPointer,
		VoidPointer
	};

	template<typename T> struct TypeOf
	{
	public:
		constexpr static FormatArgumentType value = FormatArgumentType::Unknown;
	};

#define FMATIO_TYPE(x, e) \
	template<> \
	struct TypeOf<x> \
	{ \
		constexpr static FormatArgumentType value = FormatArgumentType::e; \
	};
	
	FMATIO_TYPE(char, Char);
	FMATIO_TYPE(wchar_t, WChar);
	FMATIO_TYPE(signed char, SignedChar);
	FMATIO_TYPE(unsigned char, UnsignedChar);
	FMATIO_TYPE(signed int, SignedInt);
	FMATIO_TYPE(unsigned int, UnsignedInt);
	FMATIO_TYPE(signed short, SignedShortInt);
	FMATIO_TYPE(unsigned short, UnsignedShortInt);
	FMATIO_TYPE(signed long, SignedLongInt);
	FMATIO_TYPE(unsigned long, UnsignedLongInt);
	FMATIO_TYPE(signed long long, SignedLongLongInt);
	FMATIO_TYPE(unsigned long long, UnsignedLongLongInt);
	FMATIO_TYPE(float, SingleFloat);
	FMATIO_TYPE(double, DoubleFloat);
	FMATIO_TYPE(bool, Boolean);
	FMATIO_TYPE(char*, CharString);
	FMATIO_TYPE(const char*, CharString);
	FMATIO_TYPE(wchar_t*, WCharString);
	FMATIO_TYPE(const wchar_t*, WCharString);
	FMATIO_TYPE(null, NullPointer);
	FMATIO_TYPE(void*, VoidPointer);
	FMATIO_TYPE(const void*, VoidPointer);
#undef FORMTAXX_TYPE

	template<typename Char>
	FMATIO_API class BasicFormatArgument
	{
	private:
		FormatArgumentType type = FormatArgumentType::Unknown;
		const void* value = nullptr;

	public:
		BasicFormatArgument() noexcept;

		BasicFormatArgument(FormatArgumentType type, const void* value) noexcept;

		~BasicFormatArgument() noexcept;

	public:
		void formatInto(BasicFormatWriter<Char>& writer) const noexcept;
	};

	template<typename Char>
	FMATIO_API class BasicFormatArgumentsList
	{
	private:
		const BasicFormatArgument<Char>* arguments;
		uint32 size;

	public:
		BasicFormatArgumentsList() noexcept;
		
		BasicFormatArgumentsList(const std::initializer_list<BasicFormatArgument<Char>>& arguments) noexcept;

		~BasicFormatArgumentsList() noexcept;

	public:
		void formatArgument(BasicFormatWriter<Char>& writer, uint32 index) const noexcept;
	};

	template<typename Char, typename Value>
	FMATIO_API BasicFormatArgument<Char> makeFormatArgument(const Value& value) noexcept;
}

#include "../../source/fmatio/details/arguments.inl"

#endif
