/*******************************************************************************
 * @file arguments.hpp
 *
 * @author Joris Baranauskas (jorisb)
 *
 * Defines classes and utilitites for formatting arguments.
 *
 * @copyright © 2022-2023 by Joris Baranauskas
 *
 * This file is distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.
 * You should have received a copy of the license along with this project.
 * If not, see https://www.gnu.org/licenses/.
 ******************************************************************************/

#ifndef FMATIO_INCLUDE_FMATIO_DETAILS_ARGUMENTS_HPP
#define FMATIO_INCLUDE_FMATIO_DETAILS_ARGUMENTS_HPP

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
			static FMATIO_CONSTEXPR FormatArgumentType value = FormatArgumentType::Unknown;
		};

		/**
		 * Format argument type definition for boolean type.
		 */
		template<>
		struct TypeOf<bool>
		{
		public:
			static FMATIO_CONSTEXPR FormatArgumentType value = FormatArgumentType::Bool;
		};

		/**
		 * Format argument type definition for char type.
		 */
		template<>
		struct TypeOf<char>
		{
		public:
			static FMATIO_CONSTEXPR FormatArgumentType value = FormatArgumentType::Char;
		};

		/**
		 * Format argument type definition for signed int8 type.
		 */
		template<>
		struct TypeOf<int8>
		{
		public:
			static FMATIO_CONSTEXPR FormatArgumentType value = FormatArgumentType::SignedInt8;
		};

		/**
		 * Format argument type definition for unsigned int8 type.
		 */
		template<>
		struct TypeOf<uint8>
		{
		public:
			static FMATIO_CONSTEXPR FormatArgumentType value = FormatArgumentType::UnsignedInt8;
		};

		/**
		 * Format argument type definition for signed int16 type.
		 */
		template<>
		struct TypeOf<int16>
		{
		public:
			static FMATIO_CONSTEXPR FormatArgumentType value = FormatArgumentType::SignedInt16;
		};

		/**
		 * Format argument type definition for unsigned int16 type.
		 */
		template<>
		struct TypeOf<uint16>
		{
		public:
			static FMATIO_CONSTEXPR FormatArgumentType value = FormatArgumentType::UnsignedInt16;
		};

		/**
		 * Format argument type definition for signed int32 type.
		 */
		template<>
		struct TypeOf<int32>
		{
		public:
			static FMATIO_CONSTEXPR FormatArgumentType value = FormatArgumentType::SignedInt32;
		};

		/**
		 * Format argument type definition for unsigned int32 type.
		 */
		template<>
		struct TypeOf<uint32>
		{
		public:
			static FMATIO_CONSTEXPR FormatArgumentType value = FormatArgumentType::UnsignedInt32;
		};

		/**
		 * Format argument type definition for signed int64 type.
		 */
		template<>
		struct TypeOf<int64>
		{
		public:
			static FMATIO_CONSTEXPR FormatArgumentType value = FormatArgumentType::SignedInt64;
		};

		/**
		 * Format argument type definition for unsigned int64 type.
		 */
		template<>
		struct TypeOf<uint64>
		{
		public:
			static FMATIO_CONSTEXPR FormatArgumentType value = FormatArgumentType::UnsignedInt64;
		};

		/**
		 * Format argument type definition for float type.
		 */
		template<>
		struct TypeOf<float>
		{
		public:
			static FMATIO_CONSTEXPR FormatArgumentType value = FormatArgumentType::Float;
		};

		/**
		 * Format argument type definition for double type.
		 */
		template<>
		struct TypeOf<double>
		{
		public:
			static FMATIO_CONSTEXPR FormatArgumentType value = FormatArgumentType::Double;
		};

		/**
		 * Format argument type definition for char string type.
		 */
		template<>
		struct TypeOf<char*>
		{
		public:
			static FMATIO_CONSTEXPR FormatArgumentType value = FormatArgumentType::CharString;
		};

		/**
		 * Format argument type definition for const char string type.
		 */
		template<>
		struct TypeOf<const char*>
		{
		public:
			static FMATIO_CONSTEXPR FormatArgumentType value = FormatArgumentType::CharString;
		};

		/**
		 * Format argument type definition for nullptr type.
		 */
		template<>
		struct TypeOf<null>
		{
		public:
			static FMATIO_CONSTEXPR FormatArgumentType value = FormatArgumentType::NullPointer;
		};

		/**
		 * Format argument type definition for void pointer type.
		 */
		template<>
		struct TypeOf<void*>
		{
		public:
			static FMATIO_CONSTEXPR FormatArgumentType value = FormatArgumentType::VoidPointer;
		};

		/**
		 * A format argument, that holds it's type and pointer to it's value address in memory.
		 * 
		 * @tparam Char
		 * 		Char type to be used by format writer.
		 */
		template<typename Char>
		class BasicFormatArgument
		{
		private:
			FormatArgumentType type = FormatArgumentType::Unknown;
			const void* value = nullptr;

		public:
			/**
			 * Construct a new basic Format argument object.
			 */
			BasicFormatArgument() FMATIO_NOEXCEPT;

			/**
			 * Construct a new basic Format argument object.
			 * 
			 * @param[in] type
			 * 		Type of the argument value.
			 * 
			 * @param[in] value
			 * 		Pointer to value address in memory.
			 */
			BasicFormatArgument(FormatArgumentType type, const void* value) FMATIO_NOEXCEPT;

			/**
			 * Destroy the basic format argument object.
			 */
			~BasicFormatArgument() FMATIO_NOEXCEPT;

		public:
			/**
			 * Format argument value into the buffer using writer.
			 * 
			 * @param[inout] writer
			 * 		Writer that will pass stringified value to output buffer.
			 */
			void format(BasicFormatWriter<Char>& writer) const FMATIO_NOEXCEPT;
		};

		/**
		 * A list to store format arguments.
		 * 
		 * @tparam Char
		 * 		Char type to be used by format writer.
		 */
		template<typename Char>
		class BasicFormatArgumentsList
		{
		private:
			const BasicFormatArgument<Char>* arguments;
			uint32 size;

		public:
			/**
			 * Construct a new basic format arguments list object.
			 */
			BasicFormatArgumentsList() FMATIO_NOEXCEPT;

			/**
			 * Construct a new basic format arguments list object.
			 * 
			 * @param[in] arguments
			 * 		Format arguments list. 
			 */
			BasicFormatArgumentsList(const ::std::initializer_list<BasicFormatArgument<Char>>& arguments) FMATIO_NOEXCEPT;

			/**
			 * Destroy the basic format arguments list object.
			 */
			~BasicFormatArgumentsList() FMATIO_NOEXCEPT;

		public:
			/**
			 * Get the size of the format arguments list.
			 * 
			 * @return uint32 -
			 * 		Size of the arguments list.
			 */
			uint32 getSize() const FMATIO_NOEXCEPT;

			/**
			 * Format argument at provided index using provided format writer.
			 * 
			 * @param[inout] writer
			 * 		Writer that will format and write argument's value into output buffer.
			 * 
			 * @param[in] index
			 * 		Index of the argument that is going to be formatted.
			 */
			void format(BasicFormatWriter<Char>& writer, uint32 index) const FMATIO_NOEXCEPT;
		};

		/**
		 * Make a format argument with provided value.
		 * 
		 * @tparam Char
		 * 		Char type for the writer.
		 * 
		 * @tparam Value
		 * 		Value type.
		 * 
		 * @param[in] value
		 *		Value of the format argument.
		 * 
		 * @return BasicFormatArgument<Char> -
		 * 		Format argument.
		 */
		template<typename Char, typename Value>
		FMATIO_INLINE BasicFormatArgument<Char> makeFormatArgument(const Value& value) FMATIO_NOEXCEPT;
	}
}

#include "./arguments.inl"

#endif
