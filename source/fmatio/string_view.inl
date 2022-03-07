/*******************************************************************************
 * @file string_view.inl
 * 
 * @author Joris Baranauskas (jorisb)
 * 
 * Defines string_view.hpp implementations.
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
	BasicStringView<Char>::BasicStringView()
		: data(), size() { }

	template<typename Char>
	BasicStringView<Char>::BasicStringView(const Char* data)
		: data(data), size((uint32)strlen(data)) { }

	template<typename Char>
	BasicStringView<Char>::~BasicStringView() { }

	template<typename Char>
	const Char* BasicStringView<Char>::getData() const
	{
		return this->data;
	}

	template<typename Char>
	uint32 BasicStringView<Char>::getSize() const
	{
		return this->size;
	}

	template<typename Char>
	bool BasicStringView<Char>::isEmpty() const
	{
		return this->data == nullptr;
	}

	template<typename Char>
	const Char* BasicStringView<Char>::getBegin() const
	{
		return this->data;
	}

	template<typename Char>
	const Char* BasicStringView<Char>::getEnd() const
	{
		return this->data + this->size;
	}

	template<typename Char>
	bool BasicStringView<Char>::operator ==(const BasicStringView<Char>& other) const
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
	bool BasicStringView<Char>::operator !=(const BasicStringView<Char>& other) const
	{
		return !(*this == other);
	}

	template<typename Char>
	Char& BasicStringView<Char>::operator [](uint32 index)
	{
		return this->data[index];
	}

	template<typename Char>
	const Char& BasicStringView<Char>::operator [](uint32 index) const
	{
		return this->data[index];
	}
}