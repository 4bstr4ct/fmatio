/*******************************************************************************
 * @file arguments.inl
 * 
 * @author Joris Baranauskas (jorisb)
 * 
 * Defines format.hpp implementations.
 * 
 * @copyright © 2022-2023 by Joris Baranauskas
 * 
 * This file are distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.
 * You should have received a copy of the license along with this project.
 * If not, see https://www.gnu.org/licenses/.
 ******************************************************************************/

#include <fmatio/details/int8.hpp>
#include <fmatio/details/uint8.hpp>

#include <fmatio/details/int16.hpp>
#include <fmatio/details/uint16.hpp>

#include <fmatio/details/int32.hpp>
#include <fmatio/details/uint32.hpp>

#include <fmatio/details/int64.hpp>
#include <fmatio/details/uint64.hpp>

#include <fmatio/details/float.hpp>
#include <fmatio/details/double.hpp>

namespace fmatio
{
	namespace details
	{
		template<typename Char>
		BasicFormatArgument<Char>::BasicFormatArgument() noexcept
			: type(FormatArgumentType::Unknown), value(nullptr) { }

		template<typename Char>
		BasicFormatArgument<Char>::BasicFormatArgument(FormatArgumentType type, const void* value) noexcept
			: type(type), value(value) { }

		template<typename Char>
		BasicFormatArgument<Char>::~BasicFormatArgument() noexcept { }

		template<typename Char>
		void BasicFormatArgument<Char>::format(BasicFormatWriter<Char>& writer) const noexcept
		{
			switch (this->type)
			{
			case FormatArgumentType::Bool:
				break;

			case FormatArgumentType::WideChar:
				break;

			case FormatArgumentType::SignedInt8:
				int8Handle(writer, *static_cast<const int8*>(this->value));
				break;

			case FormatArgumentType::UnsignedInt8:
				uint8Handle(writer, *static_cast<const uint8*>(this->value));
				break;

			case FormatArgumentType::SignedInt16:
				int16Handle(writer, *static_cast<const int16*>(this->value));
				break;

			case FormatArgumentType::UnsignedInt16:
				uint16Handle(writer, *static_cast<const uint16*>(this->value));
				break;

			case FormatArgumentType::SignedInt32:
				int32Handle(writer, *static_cast<const int32*>(this->value));
				break;

			case FormatArgumentType::UnsignedInt32:
				uint32Handle(writer, *static_cast<const uint32*>(this->value));
				break;

			case FormatArgumentType::SignedInt64:
				int64Handle(writer, *static_cast<const int64*>(this->value));
				break;

			case FormatArgumentType::UnsignedInt64:
				uint64Handle(writer, *static_cast<const uint64*>(this->value));
				break;

			case FormatArgumentType::Float:
				floatHandle(writer, *static_cast<const float*>(this->value));
				break;

			case FormatArgumentType::Double:
				doubleHandle(writer, *static_cast<const double*>(this->value));
				break;

			case FormatArgumentType::NullPointer:
				break;

			case FormatArgumentType::VoidPointer:
				break;

			default:
				break;
			}
		}

		template<typename Char>
		BasicFormatArgumentsList<Char>::BasicFormatArgumentsList() noexcept
			: arguments(), size() { }

		template<typename Char>
		BasicFormatArgumentsList<Char>::BasicFormatArgumentsList(const ::std::initializer_list<BasicFormatArgument<Char>>& arguments) noexcept
			: arguments(arguments.begin()), size((uint32)arguments.size()) { }

		template<typename Char>
		BasicFormatArgumentsList<Char>::~BasicFormatArgumentsList() noexcept { }

		template<typename Char>
		uint32 BasicFormatArgumentsList<Char>::getSize() const noexcept
		{
			return this->size;
		}

		template<typename Char>
		void BasicFormatArgumentsList<Char>::format(BasicFormatWriter<Char>& writer, uint32 index) const noexcept
		{
			FMATIO_ASSERT(index >= 0 && index < this->size, "Index out of bounds!");
			this->arguments[index].format(writer);
		}

		template<typename Char, typename Value>
		BasicFormatArgument<Char> makeFormatArgument(const Value& value) noexcept
		{
			FormatArgumentType type = TypeOf<Value>::value;
			FMATIO_ASSERT(type != FormatArgumentType::Unknown, "Type of the format argument was unknown!");
			return BasicFormatArgument<Char>(type, &value);
		}
	}
}
