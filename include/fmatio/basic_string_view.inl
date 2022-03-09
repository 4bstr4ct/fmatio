/*******************************************************************************
 * @file basic_string_view.inl
 * 
 * @author Joris Baranauskas (jorisb)
 * 
 * Defines basic_string_view.hpp implementations.
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
	BasicStringView<Char>::BasicStringView() noexcept
		: data(), size() { }

	template<typename Char>
	BasicStringView<Char>::BasicStringView(const Char* data) noexcept
		: data(data), size((uint32)strlen(data)) { }

	template<typename Char>
	BasicStringView<Char>::BasicStringView(const Char* data, uint32 size) noexcept
		: data(data), size(size) { }

	template<typename Char>
	BasicStringView<Char>::~BasicStringView() noexcept { }

	template<typename Char>
	const Char* BasicStringView<Char>::getData() const noexcept
	{
		return this->data;
	}

	template<typename Char>
	uint32 BasicStringView<Char>::getSize() const noexcept
	{
		return this->size;
	}

	template<typename Char>
	bool BasicStringView<Char>::isEmpty() const noexcept
	{
		return this->data == nullptr;
	}

	template<typename Char>
	const Char* BasicStringView<Char>::getConstBegin() const noexcept
	{
		return this->data;
	}

	template<typename Char>
	const Char* BasicStringView<Char>::getConstEnd() const noexcept
	{
		return this->data + this->size;
	}

	template<typename Char>
	bool BasicStringView<Char>::operator ==(const BasicStringView<Char>& other) const noexcept
	{
		if (this == &other)
			return true;

		if (this->data == other.data)
			return true;

		if (this->size != other.size)
			return false;

		for (uint32 i = 0; i < this->size; i++)
			if (this->data[i] != other[i])
				return false;

		return true;
	}

	template<typename Char>
	bool BasicStringView<Char>::operator !=(const BasicStringView<Char>& other) const noexcept
	{
		return !(*this == other);
	}

	template<typename Char>
	const Char& BasicStringView<Char>::operator [](uint32 index) const noexcept
	{
		FMATIO_ASSERT(index >= 0 && index < this->size, "Index out of bounds!");
		return this->data[index];
	}
}