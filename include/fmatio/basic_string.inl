/*******************************************************************************
 * @file basic_string.inl
 * 
 * @author Joris Baranauskas (jorisb)
 * 
 * Defines basic_string.hpp implementations.
 * 
 * @copyright © 2022-2023 by Joris Baranauskas
 * 
 * This file is distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.
 * You should have received a copy of the license along with this project.
 * If not, see https://www.gnu.org/licenses/.
 ******************************************************************************/

#include <fmatio/details/type_traits.hpp>
#include <fmatio/details/basic_string_utilities.hpp>

namespace fmatio
{
	template<typename Char>
	BasicString<Char>::BasicString() FMATIO_NOEXCEPT
		: data(), size(), capacity() { initialize(8); }

	template<typename Char>
	BasicString<Char>::BasicString(uint32 capacity) FMATIO_NOEXCEPT
		: data(), size(), capacity() { initialize(capacity); }

	template<typename Char>
	BasicString<Char>::BasicString(const Char* const data) FMATIO_NOEXCEPT
		: data(), size(), capacity()
	{
		uint32 size = details::stringSize<Char>(data);
		initialize(size);
		copy(data, size);
	}

	template<typename Char>
	BasicString<Char>::BasicString(const BasicString& other) FMATIO_NOEXCEPT
		: data(), size(), capacity()
	{
		initialize(other.getCapacity());
		copy(other.getData(), other.getSize());
	}

#if defined(FMATIO_MOVE_SEMANTICS_ENABLED) && FMATIO_MOVE_SEMANTICS_ENABLED == 1
	template<typename Char>
	BasicString<Char>::BasicString(BasicString&& other) FMATIO_NOEXCEPT
		: data(other.data), size(other.size), capacity(other.capacity) { other.data = nullptr; }
#endif

	template<typename Char>
	BasicString<Char>::~BasicString() FMATIO_NOEXCEPT
	{
		deallocate();
	}

	template<typename Char>
	void BasicString<Char>::initialize(uint32 capacity) FMATIO_NOEXCEPT
	{
		this->data = (Char*)operator new(capacity * sizeof(Char));
		this->capacity = capacity;
	}

	template<typename Char>
	void BasicString<Char>::reallocate(uint32 newCapacity) FMATIO_NOEXCEPT
	{
		Char* temp = (Char*)operator new(newCapacity * sizeof(Char));

		if (this->size > newCapacity)
			this->size = newCapacity;

		for (uint32 i = 0; i < this->size; i++)
			temp[i] = details::move(this->data[i]);

		for (uint32 i = 0; i < this->size; i++)
			this->data[i].~Char();

		::operator delete(this->data, this->capacity * sizeof(Char));
		this->data = temp;
		this->capacity = newCapacity;
	}

	template<typename Char>
	void BasicString<Char>::copy(const Char* const data, uint32 size) FMATIO_NOEXCEPT
	{
		FMATIO_ASSERT(this->size >= size, "Provided cstring is too big to copy!");
		
		for (uint32 i = 0; i < size; i++)
			this->data[i] = details::move(data[i]);
	}

	template<typename Char>
	void BasicString<Char>::deallocate() FMATIO_NOEXCEPT
	{
		clear();
		::operator delete(this->data, this->capacity * sizeof(Char));
	}

	template<typename Char>
	Char* BasicString<Char>::getData() FMATIO_NOEXCEPT
	{
		return this->data;
	}

	template<typename Char>
	const Char* BasicString<Char>::getData() const FMATIO_NOEXCEPT
	{
		return this->data;
	}

	template<typename Char>
	uint32 BasicString<Char>::getSize() const FMATIO_NOEXCEPT
	{
		return this->size;
	}

	template<typename Char>
	uint32 BasicString<Char>::getCapacity() const FMATIO_NOEXCEPT
	{
		return this->capacity;
	}

	template<typename Char>
	bool BasicString<Char>::isEmpty() const FMATIO_NOEXCEPT
	{
		return this->data == nullptr;
	}

	template<typename Char>
	void BasicString<Char>::append(const Char* const string) FMATIO_NOEXCEPT
	{
		append(string, details::stringSize<Char>(string));
	}

	template<typename Char>
	void BasicString<Char>::append(const Char* const begin, uint32 size) FMATIO_NOEXCEPT
	{
		if (this->size + size + 1 > this->capacity)
			reallocate(this->capacity + size + 1);

		details::stringCopy<Char>(this->data + this->size, begin, size);
		this->size += size;
	}

	template<typename Char>
	void BasicString<Char>::clear() FMATIO_NOEXCEPT
	{
		for (uint32 i = 0; i < this->size; i++)
			this->data[i].~Char();

		this->size = 0;
	}

	template<typename Char>
	Char* BasicString<Char>::getBegin() FMATIO_NOEXCEPT
	{
		return this->data;
	}
	
	template<typename Char>
	Char* BasicString<Char>::getEnd() FMATIO_NOEXCEPT
	{
		return this->data + this->size;
	}

	template<typename Char>
	const Char* BasicString<Char>::getConstBegin() const FMATIO_NOEXCEPT
	{
		return this->data;
	}

	template<typename Char>
	const Char* BasicString<Char>::getConstEnd() const FMATIO_NOEXCEPT
	{
		return this->data + this->size;
	}

	template<typename Char>
	BasicString<Char>& BasicString<Char>::operator =(const BasicString<Char>& other) FMATIO_NOEXCEPT
	{
		deallocate();
		initialize(other.getCapacity());
		copy(other.getData(), other.getSize());
		this->size = other.getSize();
		return *this;
	}

#if defined(FMATIO_MOVE_SEMANTICS_ENABLED) && FMATIO_MOVE_SEMANTICS_ENABLED == 1
	template<typename Char>
	BasicString<Char>& BasicString<Char>::operator =(BasicString<Char>&& other) FMATIO_NOEXCEPT
	{
		if (this == &other)
			return *this;

		this->data = other.data;
		this->size = other.size;
		this->capacity = other.capacity;
		other.data = nullptr;
		return *this;
	}
#endif

	template<typename Char>
	bool BasicString<Char>::operator ==(const BasicString& other) const FMATIO_NOEXCEPT
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
	bool BasicString<Char>::operator !=(const BasicString& other) const FMATIO_NOEXCEPT
	{
		return !(*this == other);
	}

	template<typename Char>
	Char& BasicString<Char>::operator [](uint32 index) FMATIO_NOEXCEPT
	{
		FMATIO_ASSERT(index >= 0 && index < this->size, "Index out of bounds!");
		return this->data[index];
	}

	template<typename Char>
	const Char& BasicString<Char>::operator [](uint32 index) const FMATIO_NOEXCEPT
	{
		FMATIO_ASSERT(index >= 0 && index < this->size, "Index out of bounds!");
		return this->data[index];
	}
}
