/*******************************************************************************
 * @file arguments.inl
 * 
 * @author Joris Baranauskas (jorisb)
 * 
 * Defines format.hpp implementations.
 * 
 * @copyright © 2022-2023 by Joris Baranauskas
 * 
 * This file is distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.
 * You should have received a copy of the license along with this project.
 * If not, see https://www.gnu.org/licenses/.
 ******************************************************************************/

#include <fmatio/details/types/bool.hpp>
#include <fmatio/details/types/char.hpp>

#include <fmatio/details/types/int8.hpp>
#include <fmatio/details/types/uint8.hpp>

#include <fmatio/details/types/int16.hpp>
#include <fmatio/details/types/uint16.hpp>

#include <fmatio/details/types/int32.hpp>
#include <fmatio/details/types/uint32.hpp>

#include <fmatio/details/types/int64.hpp>
#include <fmatio/details/types/uint64.hpp>

#include <fmatio/details/types/float.hpp>
#include <fmatio/details/types/double.hpp>

#include <fmatio/details/types/char_string.hpp>

namespace fmatio
{
	namespace details
	{
		template<typename Char>
		BasicFormatArgument<Char>::BasicFormatArgument() FMATIO_NOEXCEPT
			: type(FormatArgumentType::Unknown), value(nullptr) { }

		template<typename Char>
		BasicFormatArgument<Char>::BasicFormatArgument(FormatArgumentType type, const void* value) FMATIO_NOEXCEPT
			: type(type), value(value) { }

		template<typename Char>
		BasicFormatArgument<Char>::~BasicFormatArgument() FMATIO_NOEXCEPT { }

		template<typename Char>
		void BasicFormatArgument<Char>::format(BasicFormatWriter<Char>& writer) const FMATIO_NOEXCEPT
		{
			switch (this->type)
			{
			case FormatArgumentType::Bool:
				boolHandle(writer, *static_cast<const bool*>(this->value));
				break;

			case FormatArgumentType::Char:
				charHandle(writer, *static_cast<const char*>(this->value));
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

			case FormatArgumentType::CharString:
				charStringHandle(writer, *static_cast<const char* const *>(this->value));
				break;

			case FormatArgumentType::NullPointer:
				charStringHandle(writer, FormatTraits<Char>::nullptrStringified);
				break;

			default:
				break;
			}
		}

		template<typename Char>
		BasicFormatArgumentsList<Char>::BasicFormatArgumentsList() FMATIO_NOEXCEPT
			: arguments(), size() { }

		template<typename Char>
		BasicFormatArgumentsList<Char>::BasicFormatArgumentsList(const ::std::initializer_list<BasicFormatArgument<Char>>& argumentsList) FMATIO_NOEXCEPT
			: arguments(argumentsList.begin()), size((uint32)argumentsList.size()) { }

		template<typename Char>
		BasicFormatArgumentsList<Char>::~BasicFormatArgumentsList() FMATIO_NOEXCEPT { }

		template<typename Char>
		uint32 BasicFormatArgumentsList<Char>::getSize() const FMATIO_NOEXCEPT
		{
			return this->size;
		}

		template<typename Char>
		const BasicFormatArgument<Char>& BasicFormatArgumentsList<Char>::operator [](uint32 index) const FMATIO_NOEXCEPT
		{
			FMATIO_ASSERT(index >= 0 && index < this->size, "Index out of bounds!");
			return this->arguments[index];
		}


		template<typename Char, typename Value>
		FMATIO_INLINE BasicFormatArgument<Char> makeFormatArgument(const Value& value) FMATIO_NOEXCEPT
		{
			FormatArgumentType type = TypeOf<Value>::value;

			if (type != FormatArgumentType::Unknown)
				return BasicFormatArgument<Char>(type, &value);

			FMATIO_ASSERT(false, "Provided argument type is not supported!");
			return BasicFormatArgument<Char>();
		}
	}
}
