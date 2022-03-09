/*******************************************************************************
 * @file basic_string.inl
 * 
 * @author Joris Baranauskas (jorisb)
 * 
 * Defines basic_string.hpp implementations.
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
	BasicString<Char>::BasicString() noexcept
		: data(), size(), capacity() { initialize(8); }

	template<typename Char>
	BasicString<Char>::BasicString(uint32 capacity) noexcept
		: data(), size(), capacity() { initialize(capacity); }

	template<typename Char>
	BasicString<Char>::BasicString(const Char* const data) noexcept
		: data(), size(), capacity()
	{
		uint32 size = ::strlen(data);
		initialize(size);
		copy(data, size);
	}

	template<typename Char>
	BasicString<Char>::BasicString(const BasicString& other) noexcept
		: data(), size(), capacity()
	{
		initialize(other.getCapacity());
		copy(other.getData(), other.getSize());
	}

#if defined(FMATIO_MOVE_SEMANTICS_ENABLED) && FMATIO_MOVE_SEMANTICS_ENABLED == 1
	template<typename Char>
	BasicString<Char>::BasicString(BasicString&& other) noexcept
		: data(other.data), size(other.size), capacity(other.capacity) { other.data = nullptr; }
#endif

	template<typename Char>
	BasicString<Char>::~BasicString() noexcept
	{
		deallocate();
	}

	template<typename Char>
	void BasicString<Char>::initialize(uint32 capacity) noexcept
	{
		this->data = (Char*)operator new(capacity * sizeof(Char));
		this->capacity = capacity;
	}

	template<typename Char>
	void BasicString<Char>::reallocate(uint32 newCapacity) noexcept
	{
		Char* temp = (Char*)operator new(newCapacity * sizeof(Char));

		if (this->size > newCapacity)
			this->size = newCapacity;

		for (uint32 i = 0; i < this->size; i++)
			temp[i] = ::std::move(this->data[i]);

		for (uint32 i = 0; i < this->size; i++)
			this->data[i].~Char();

		::operator delete(this->data, this->capacity * sizeof(Char));
		this->data = temp;
		this->capacity = newCapacity;
	}

	template<typename Char>
	void BasicString<Char>::copy(const Char* const data, uint32 size) noexcept
	{
		FMATIO_ASSERT(this->size >= size, "Provided cstring is too big to copy!");
		
		for (uint32 i = 0; i < size; i++)
			this->data[i] = ::std::move(data[i]);
	}

	template<typename Char>
	void BasicString<Char>::deallocate() noexcept
	{
		clear();
		::operator delete(this->data, this->capacity * sizeof(Char));
	}

	template<typename Char>
	const Char* BasicString<Char>::getData() const noexcept
	{
		return this->data;
	}

	template<typename Char>
	uint32 BasicString<Char>::getSize() const noexcept
	{
		return this->size;
	}

	template<typename Char>
	uint32 BasicString<Char>::getCapacity() const noexcept
	{
		return this->capacity;
	}

	template<typename Char>
	bool BasicString<Char>::isEmpty() const noexcept
	{
		return this->data == nullptr;
	}

	template<typename Char>
	void BasicString<Char>::append(const Char* const string) noexcept
	{
		append(string, ::strlen(string));
	}

	template<typename Char>
	void BasicString<Char>::append(const Char* const begin, uint32 size) noexcept
	{
		if (this->size + size + 1 > this->capacity)
			reallocate(this->capacity + size + 1);

		::memcpy(this->data + this->size, begin, size);
		this->size += size;
	}

	template<typename Char>
	void BasicString<Char>::clear() noexcept
	{
		for (uint32 i = 0; i < this->size; i++)
			this->data[i].~Char();

		this->size = 0;
	}

	template<typename Char>
	Char* BasicString<Char>::getBegin() noexcept
	{
		return this->data;
	}
	
	template<typename Char>
	Char* BasicString<Char>::getEnd() noexcept
	{
		return this->data + this->size;
	}

	template<typename Char>
	const Char* BasicString<Char>::getConstBegin() const noexcept
	{
		return this->data;
	}

	template<typename Char>
	const Char* BasicString<Char>::getConstEnd() const noexcept
	{
		return this->data + this->size;
	}

	template<typename Char>
	BasicString<Char>& BasicString<Char>::operator =(const BasicString<Char>& other) noexcept
	{
		deallocate();
		initialize(other.getCapacity());
		copy(other.getData(), other.getSize());
		this->size = other.getSize();
		return *this;
	}

#if defined(FMATIO_MOVE_SEMANTICS_ENABLED) && FMATIO_MOVE_SEMANTICS_ENABLED == 1
	template<typename Char>
	BasicString<Char>& BasicString<Char>::operator =(BasicString<Char>&& other) noexcept
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
	bool BasicString<Char>::operator ==(const BasicString& other) const noexcept
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
	bool BasicString<Char>::operator !=(const BasicString& other) const noexcept
	{
		return !(*this == other);
	}

	template<typename Char>
	Char& BasicString<Char>::operator [](uint32 index) noexcept
	{
		FMATIO_ASSERT(index >= 0 && index < this->size, "Index out of bounds!");
		return this->data[index];
	}

	template<typename Char>
	const Char& BasicString<Char>::operator [](uint32 index) const noexcept
	{
		FMATIO_ASSERT(index >= 0 && index < this->size, "Index out of bounds!");
		return this->data[index];
	}
}
