/*******************************************************************************
 * @file type_traits.hpp
 *
 * @author Joris Baranauskas (jorisb)
 *
 * Defines classes and utilitites for type traits.
 *
 * @copyright © 2022-2023 by Joris Baranauskas
 *
 * This file is distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.
 * You should have received a copy of the license along with this project.
 * If not, see https://www.gnu.org/licenses/.
 ******************************************************************************/

#ifndef FMATIO_INCLUDE_FMATIO_DETAILS_TYPE_TRAITS_HPP
#define FMATIO_INCLUDE_FMATIO_DETAILS_TYPE_TRAITS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#	pragma once
#endif

#include <fmatio/core.hpp>
#include <fmatio/types.hpp>

namespace fmatio
{
	namespace details
	{
		/**
		 * Defines types of format arguments.
		 */
		enum class FormatArgumentType : uint8
		{
			Unknown,

			Bool,
			Char,

			SignedInt8,
			UnsignedInt8,

			SignedInt16,
			UnsignedInt16,

			SignedInt32,
			UnsignedInt32,

			SignedInt64,
			UnsignedInt64,

			Float,
			Double,

			CharString,
			NullPointer,
			VoidPointer
		};

		/**
		 * Format argument type definition for unknown type.
		 * 
		 * @tparam T
		 * 		Type of the argument.
		 */
		template<typename T>
		struct TypeOf
		{
		public:
			static FMATIO_CONSTEXPR const FormatArgumentType value = FormatArgumentType::Unknown;
		};

		/**
		 * Format argument type definition for boolean type.
		 */
		template<>
		struct TypeOf<bool>
		{
		public:
			static FMATIO_CONSTEXPR const FormatArgumentType value = FormatArgumentType::Bool;
		};

		/**
		 * Format argument type definition for char type.
		 */
		template<>
		struct TypeOf<char>
		{
		public:
			static FMATIO_CONSTEXPR const FormatArgumentType value = FormatArgumentType::Char;
		};

		/**
		 * Format argument type definition for signed int8 type.
		 */
		template<>
		struct TypeOf<int8>
		{
		public:
			static FMATIO_CONSTEXPR const FormatArgumentType value = FormatArgumentType::SignedInt8;
		};

		/**
		 * Format argument type definition for unsigned int8 type.
		 */
		template<>
		struct TypeOf<uint8>
		{
		public:
			static FMATIO_CONSTEXPR const FormatArgumentType value = FormatArgumentType::UnsignedInt8;
		};

		/**
		 * Format argument type definition for signed int16 type.
		 */
		template<>
		struct TypeOf<int16>
		{
		public:
			static FMATIO_CONSTEXPR const FormatArgumentType value = FormatArgumentType::SignedInt16;
		};

		/**
		 * Format argument type definition for unsigned int16 type.
		 */
		template<>
		struct TypeOf<uint16>
		{
		public:
			static FMATIO_CONSTEXPR const FormatArgumentType value = FormatArgumentType::UnsignedInt16;
		};

		/**
		 * Format argument type definition for signed int32 type.
		 */
		template<>
		struct TypeOf<int32>
		{
		public:
			static FMATIO_CONSTEXPR const FormatArgumentType value = FormatArgumentType::SignedInt32;
		};

		/**
		 * Format argument type definition for unsigned int32 type.
		 */
		template<>
		struct TypeOf<uint32>
		{
		public:
			static FMATIO_CONSTEXPR const FormatArgumentType value = FormatArgumentType::UnsignedInt32;
		};

		/**
		 * Format argument type definition for signed int64 type.
		 */
		template<>
		struct TypeOf<int64>
		{
		public:
			static FMATIO_CONSTEXPR const FormatArgumentType value = FormatArgumentType::SignedInt64;
		};

		/**
		 * Format argument type definition for unsigned int64 type.
		 */
		template<>
		struct TypeOf<uint64>
		{
		public:
			static FMATIO_CONSTEXPR const FormatArgumentType value = FormatArgumentType::UnsignedInt64;
		};

		/**
		 * Format argument type definition for float type.
		 */
		template<>
		struct TypeOf<float>
		{
		public:
			static FMATIO_CONSTEXPR const FormatArgumentType value = FormatArgumentType::Float;
		};

		/**
		 * Format argument type definition for double type.
		 */
		template<>
		struct TypeOf<double>
		{
		public:
			static FMATIO_CONSTEXPR const FormatArgumentType value = FormatArgumentType::Double;
		};

		/**
		 * Format argument type definition for char string type.
		 */
		template<>
		struct TypeOf<char*>
		{
		public:
			static FMATIO_CONSTEXPR const FormatArgumentType value = FormatArgumentType::CharString;
		};

		/**
		 * Format argument type definition for signed char string type.
		 */
		template<>
		struct TypeOf<signed char*>
		{
		public:
			static FMATIO_CONSTEXPR const FormatArgumentType value = FormatArgumentType::CharString;
		};

		/**
		 * Format argument type definition for unsigned char string type.
		 */
		template<>
		struct TypeOf<unsigned char*>
		{
		public:
			static FMATIO_CONSTEXPR const FormatArgumentType value = FormatArgumentType::CharString;
		};

		/**
		 * Format argument type definition for const char string type.
		 */
		template<>
		struct TypeOf<const char*>
		{
		public:
			static FMATIO_CONSTEXPR const FormatArgumentType value = FormatArgumentType::CharString;
		};

		/**
		 * Format argument type definition for const signed char string type.
		 */
		template<>
		struct TypeOf<const signed char*>
		{
		public:
			static FMATIO_CONSTEXPR const FormatArgumentType value = FormatArgumentType::CharString;
		};

		/**
		 * Format argument type definition for const unsigned char string type.
		 */
		template<>
		struct TypeOf<const unsigned char*>
		{
		public:
			static FMATIO_CONSTEXPR const FormatArgumentType value = FormatArgumentType::CharString;
		};

		/**
		 * Format argument type definition for nullptr type.
		 */
		template<>
		struct TypeOf<null>
		{
		public:
			static FMATIO_CONSTEXPR const FormatArgumentType value = FormatArgumentType::NullPointer;
		};

		/**
		 * Format argument type definition for void pointer type.
		 */
		template<>
		struct TypeOf<void*>
		{
		public:
			static FMATIO_CONSTEXPR const FormatArgumentType value = FormatArgumentType::VoidPointer;
		};

		/**
		 * Format argument type definition for const void pointer type.
		 */
		template<>
		struct TypeOf<const void*>
		{
		public:
			static FMATIO_CONSTEXPR const FormatArgumentType value = FormatArgumentType::VoidPointer;
		};

		template<typename T>
		struct RemoveReference
		{
		public:
			using Type = T;
		};

		template<typename T>
		struct RemoveReference<T&>
		{
		public:
			using Type = T;
		};

		template<typename T>
		struct RemoveReference<T&&>
		{
		public:
			using Type = T;
		};

		template<typename T>
		using RemoveReferenceType = typename RemoveReference<T>::Type;

		template<typename T>
		struct RemoveExtent
		{
		public:
			using Type = T;
		};

		template<typename T, uint32 size>
		struct RemoveExtent<T[size]>
		{
		public:
			using Type = T;
		};

		template<typename T>
		struct RemoveExtent<T[]>
		{
		public:
			using Type = T;
		};

		template<typename T>
		using RemoveExtentType = typename RemoveExtent<T>::Type;

		template<typename T>
		using DecayedIfArray = ::std::conditional_t<::std::is_array_v<T>, RemoveExtentType<T> const*, T>;

		template<typename T>
		using Formattable = DecayedIfArray<RemoveReferenceType<T>>;
	}
}

#endif
