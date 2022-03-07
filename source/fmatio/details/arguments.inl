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

namespace fmatio
{
	template<typename Char>
	BasicFormatArgument<Char>::BasicFormatArgument() noexcept
		: type(FormatArgumentType::Unknown), value() { }

	template<typename Char>
	BasicFormatArgument<Char>::BasicFormatArgument(FormatArgumentType type, const void* value) noexcept
		: type(type), value(value) { }

	template<typename Char>
	BasicFormatArgument<Char>::~BasicFormatArgument() noexcept { }

	template<typename Char>
	void BasicFormatArgument<Char>::formatInto(BasicFormatWriter<Char>& writer) const noexcept
	{
		switch (this->type)
		{
		case FormatArgumentType::Char:
			// _detail::write_char(writer, *static_cast<char const*>(this->value));
			break;

		case FormatArgumentType::WChar:
			// _detail::write_char(writer, *static_cast<wchar_t const*>(this->value));
			break;

		case FormatArgumentType::SignedChar:
			// _detail::write_integer(writer, *static_cast<signed char const*>(this->value));
			break;

		case FormatArgumentType::UnsignedChar:
			// _detail::write_integer(writer, *static_cast<unsigned char const*>(this->value));
			break;

		case FormatArgumentType::SignedInt:
			// _detail::write_integer(writer, *static_cast<signed int const*>(this->value));
			break;

		case FormatArgumentType::UnsignedInt:
			// _detail::write_integer(writer, *static_cast<unsigned int const*>(this->value));
			break;

		case FormatArgumentType::SignedShortInt:
			// _detail::write_integer(writer, *static_cast<signed short const*>(this->value));
			break;

		case FormatArgumentType::UnsignedShortInt:
			// _detail::write_integer(writer, *static_cast<unsigned short const*>(this->value));
			break;

		case FormatArgumentType::SignedLongInt:
			// _detail::write_integer(writer, *static_cast<signed long const*>(this->value));
			break;

		case FormatArgumentType::UnsignedLongInt:
			// _detail::write_integer(writer, *static_cast<unsigned long const*>(this->value));
			break;

		case FormatArgumentType::SignedLongLongInt:
			// _detail::write_integer(writer, *static_cast<signed long long const*>(this->value));
			break;

		case FormatArgumentType::UnsignedLongLongInt:
			// _detail::write_integer(writer, *static_cast<unsigned long long const*>(this->value));
			break;

		case FormatArgumentType::SingleFloat:
			// _detail::write_float(writer, *static_cast<float const*>(this->value));
			break;

		case FormatArgumentType::DoubleFloat:
			// _detail::write_float(writer, *static_cast<double const*>(this->value));
			break;

		case FormatArgumentType::Boolean:
			// _detail::write_string(writer, *static_cast<bool const*>(this->value) ? _detail::FormatTraits<CharT>::sTrue : _detail::FormatTraits<CharT>::sFalse);
			break;

		case FormatArgumentType::CharString:
			// _detail::write_string(writer, string_view(*static_cast<char const* const*>(this->value)));
			break;

		case FormatArgumentType::WCharString:
			// _detail::write_string(writer, wstring_view(*static_cast<wchar_t const* const*>(this->value)));
			break;

		case FormatArgumentType::NullPointer:
			// _detail::write_string(writer, _detail::FormatTraits<CharT>::sNullptr);
			break;

		case FormatArgumentType::VoidPointer:
			// _detail::write_integer(writer, reinterpret_cast<std::uintptr_t>(*static_cast<void const* const*>(this->value)));
			break;

		default:
			break;
		}
	}

	template<typename Char>
	BasicFormatArgumentsList<Char>::BasicFormatArgumentsList() noexcept
		: arguments(), size() { }
	
	template<typename Char>
	BasicFormatArgumentsList<Char>::BasicFormatArgumentsList(const std::initializer_list<BasicFormatArgument<Char>>& arguments) noexcept
		: arguments(arguments.begin()), size((uint32)arguments.size()) { }

	template<typename Char>
	BasicFormatArgumentsList<Char>::~BasicFormatArgumentsList() noexcept { }

	template<typename Char>
	void BasicFormatArgumentsList<Char>::formatArgument(BasicFormatWriter<Char>& writer, uint32 index) const noexcept
	{
		FMATIO_ASSERT(index >= 0 && index < this->size, "Index out of bounds!");
		return this->arguments[index].formatInto(writer);
	}

	template<typename Char, typename Value>
	FMATIO_API BasicFormatArgument<Char> makeFormatArgument(const Value& value) noexcept
	{
		FormatArgumentType type = TypeOf<Value>::value;

		if (type != FormatArgumentType::Unknown)
			return { type, &value };

		return { };
	}
}
