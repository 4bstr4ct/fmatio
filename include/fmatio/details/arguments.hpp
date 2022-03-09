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
			ConstCharString,

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
			constexpr static FormatArgumentType value = FormatArgumentType::Unknown;
		};

		/**
		 * Format argument type definition for boolean type.
		 */
		template<>
		struct TypeOf<bool>
		{
		public:
			constexpr static FormatArgumentType value = FormatArgumentType::Bool;
		};

		/**
		 * Format argument type definition for signed int8 type.
		 */
		template<>
		struct TypeOf<int8>
		{
		public:
			constexpr static FormatArgumentType value = FormatArgumentType::SignedInt8;
		};

		/**
		 * Format argument type definition for unsigned int8 type.
		 */
		template<>
		struct TypeOf<uint8>
		{
		public:
			constexpr static FormatArgumentType value = FormatArgumentType::UnsignedInt8;
		};

		/**
		 * Format argument type definition for signed int16 type.
		 */
		template<>
		struct TypeOf<int16>
		{
		public:
			constexpr static FormatArgumentType value = FormatArgumentType::SignedInt16;
		};

		/**
		 * Format argument type definition for unsigned int16 type.
		 */
		template<>
		struct TypeOf<uint16>
		{
		public:
			constexpr static FormatArgumentType value = FormatArgumentType::UnsignedInt16;
		};

		/**
		 * Format argument type definition for signed int32 type.
		 */
		template<>
		struct TypeOf<int32>
		{
		public:
			constexpr static FormatArgumentType value = FormatArgumentType::SignedInt32;
		};

		/**
		 * Format argument type definition for unsigned int32 type.
		 */
		template<>
		struct TypeOf<uint32>
		{
		public:
			constexpr static FormatArgumentType value = FormatArgumentType::UnsignedInt32;
		};

		/**
		 * Format argument type definition for signed int64 type.
		 */
		template<>
		struct TypeOf<int64>
		{
		public:
			constexpr static FormatArgumentType value = FormatArgumentType::SignedInt64;
		};

		/**
		 * Format argument type definition for unsigned int64 type.
		 */
		template<>
		struct TypeOf<uint64>
		{
		public:
			constexpr static FormatArgumentType value = FormatArgumentType::UnsignedInt64;
		};

		/**
		 * Format argument type definition for float type.
		 */
		template<>
		struct TypeOf<float>
		{
		public:
			constexpr static FormatArgumentType value = FormatArgumentType::Float;
		};

		/**
		 * Format argument type definition for double type.
		 */
		template<>
		struct TypeOf<double>
		{
		public:
			constexpr static FormatArgumentType value = FormatArgumentType::Double;
		};

		/**
		 * Format argument type definition for char string type.
		 */
		template<>
		struct TypeOf<char*>
		{
		public:
			constexpr static FormatArgumentType value = FormatArgumentType::CharString;
		};

		/**
		 * Format argument type definition for const char string type.
		 */
		template<>
		struct TypeOf<const char*>
		{
		public:
			constexpr static FormatArgumentType value = FormatArgumentType::ConstCharString;
		};

		/**
		 * Format argument type definition for nullptr type.
		 */
		template<>
		struct TypeOf<null>
		{
		public:
			constexpr static FormatArgumentType value = FormatArgumentType::NullPointer;
		};

		/**
		 * Format argument type definition for void pointer type.
		 */
		template<>
		struct TypeOf<void*>
		{
		public:
			constexpr static FormatArgumentType value = FormatArgumentType::VoidPointer;
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
			BasicFormatArgument() noexcept;

			/**
			 * Construct a new basic Format argument object.
			 * 
			 * @param[in] type
			 * 		Type of the argument value.
			 * 
			 * @param[in] value
			 * 		Pointer to value address in memory.
			 */
			BasicFormatArgument(FormatArgumentType type, const void* value) noexcept;

			/**
			 * Destroy the basic format argument object.
			 */
			~BasicFormatArgument() noexcept;

		public:
			/**
			 * Format argument value into the buffer using writer.
			 * 
			 * @param[inout] writer
			 * 		Writer that will pass stringified value to output buffer.
			 */
			void format(BasicFormatWriter<Char>& writer) const noexcept;
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
			BasicFormatArgumentsList() noexcept;

			/**
			 * Construct a new basic format arguments list object.
			 * 
			 * @param[in] arguments
			 * 		Format arguments list. 
			 */
			BasicFormatArgumentsList(const ::std::initializer_list<BasicFormatArgument<Char>>& arguments) noexcept;

			/**
			 * Destroy the basic format arguments list object.
			 */
			~BasicFormatArgumentsList() noexcept;

		public:
			/**
			 * Get the size of the format arguments list.
			 * 
			 * @return uint32 -
			 * 		Size of the arguments list.
			 */
			uint32 getSize() const noexcept;

			/**
			 * Format argument at provided index using provided format writer.
			 * 
			 * @param[inout] writer
			 * 		Writer that will format and write argument's value into output buffer.
			 * 
			 * @param[in] index
			 * 		Index of the argument that is going to be formatted.
			 */
			void format(BasicFormatWriter<Char>& writer, uint32 index) const noexcept;
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
		 * 
		 * @return BasicFormatArgument<Char> -
		 * 		Format argument.
		 */
		template<typename Char, typename Value>
		BasicFormatArgument<Char> makeFormatArgument(const Value& value) noexcept;
	}
}

#include "./arguments.inl"

#endif
