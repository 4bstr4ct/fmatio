/*******************************************************************************
 * @file fmatio_all.hpp
 *
 * @author Joris Baranauskas (jorisb)
 *
 * Contains all fmatio library files and source code.
 *
 * @copyright © 2022-2023 by Joris Baranauskas
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or distribute
 * this software, either in source code form or as a compiled binary, for any
 * purpose, commercial or non - commercial, and by any means.
 ******************************************************************************/

 /*******************************************************************************
  * fmatio - C++ header-only formatting library.
  * This project is free software released into the public domain.
  *
  * Anyone is free to copy, modify, publish, use, compile, sell, or distribute
  * this software, either in source code form or as a compiled binary, for any
  * purpose, commercial or non - commercial, and by any means.
  *
  * In jurisdictions that recognize copyright laws, the author or authors of
  * this software dedicate any and all copyright interest in the software to
  * the public domain.
  *
  * The software is provided "as is", without warranty of any kind, express or
  * implied, including but not limited to the warranties of merchantability,
  * fitness for a particular purpose and noninfringement. In no event shall the
  * authors be liable for any claim, damages or other liability, whether in an
  * action of contract, tort or otherwise, arising from, out of or in connection
  * with the software or the use or other dealings in the software.
  *
  * Author: Joris Baranauskas (jorisb)
  ******************************************************************************/

#ifndef FMATIO_ALL_HPP
#define FMATIO_ALL_HPP

#include <ostream>
#include <string>

#pragma region Core
#if FMATIO_DEBUG
#	include <iostream>
#	define FMATIO_ASSERT(expression, message) \
{ \
	if (!(expression)) \
	{ \
		::std::cerr << "Assertion failed: " << message << "\n\tFile: " << __FILE__ << ". Line: " << __LINE__ << "." << ::std::endl; \
		::std::exit(-1); \
	} \
}
#else
#	define FMATIO_ASSERT(expression, message)
#endif

#if !defined(FMATIO_MOVE_SEMANTICS_ENABLED)
#	if !defined(PYRONET_DISABLE_MOVE_SEMANTICS)
#		if defined(__clang__)
#			if __has_feature(__cxx_rvalue_references__)
#				define FMATIO_MOVE_SEMANTICS_ENABLED 1
#			endif
#		endif
#		if defined(__GNUC__)
#			if ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 8)) || (__GNUC__ > 4)
#				if (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#					define FMATIO_MOVE_SEMANTICS_ENABLED 1
#				endif
#			endif
#		endif
#		if defined(_MSC_VER) && (_MSC_VER >= 1700)
#			define FMATIO_MOVE_SEMANTICS_ENABLED 1
#		endif
#		if defined(__INTEL_CXX11_MODE__)
#			if defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 1500)
#				define FMATIO_MOVE_SEMANTICS_ENABLED 1
#			endif
#			if defined(__ICL) && (__ICL >= 1500)
#				define FMATIO_MOVE_SEMANTICS_ENABLED 1
#			endif
#		endif
#	endif
#endif
#pragma endregion

namespace fmatio
{
#pragma region Types
	/**
	 * A type represeting null pointer
	 */
	using null = decltype(__nullptr);

	/**
	 * A type representing signed char.
	 */
	using int8 = signed char;

	/**
	 * A type representing unsigned char.
	 */
	using uint8 = unsigned char;

	/**
	 * A type representing unsigned char.
	 */
	using byte = unsigned char;

	/**
	 * A type representing signed short.
	 */
	using int16 = signed short;

	/**
	 * A type representing unsigned short.
	 */
	using uint16 = unsigned short;

	/**
	 * A type representing signed int.
	 */
	using int32 = signed int;

	/**
	 * A type representing unsigned int.
	 */
	using uint32 = unsigned int;

	/**
	 * A type representing signed long long.
	 */
	using int64 = signed long long;

	/**
	 * A type representing unsigned long long.
	 */
	using uint64 = unsigned long long;

	/**
	 * A type representing wide char.
	 */
	using wchar = wchar_t;
#pragma endregion

#pragma region BasicStringView
	template<typename Char>
	class BasicStringView
	{
	public:
		/**
		 * Define a const iterator to iterate through the data.
		 */
		using ConstIterator = const Char*;

		/**
		 * Define a public typedef for char type used in this class.
		 */
		using CharType = Char;

		/**
		 * Define a public typedef for value type used in this class.
		 */
		using ValueType = Char;

	private:
		const Char* data;
		uint32 size;

	public:
		BasicStringView() noexcept;

		BasicStringView(const Char* data) noexcept;

		BasicStringView(const Char* data, uint32 size) noexcept;

		BasicStringView(const BasicStringView& other) noexcept = default;

#if defined(FMATIO_MOVE_SEMANTICS_ENABLED) && FMATIO_MOVE_SEMANTICS_ENABLED == 1
		BasicStringView(BasicStringView&& other) noexcept = default;
#endif

		~BasicStringView() noexcept;

	public:
		const Char* getData() const noexcept;

		uint32 getSize() const noexcept;

		bool isEmpty() const noexcept;

		const Char* getConstBegin() const noexcept;

		const Char* getConstEnd() const noexcept;

	public:
		BasicStringView<Char>& operator =(const BasicStringView& other) noexcept = default;

#if defined(FMATIO_MOVE_SEMANTICS_ENABLED) && FMATIO_MOVE_SEMANTICS_ENABLED == 1
		BasicStringView<Char>& operator =(BasicStringView&& other) noexcept = default;
#endif

		bool operator ==(const BasicStringView& other) const noexcept;

		bool operator !=(const BasicStringView& other) const noexcept;

		const Char& operator [](uint32 index) const noexcept;
	};
#pragma endregion

#pragma region BasicString
	template<typename Char>
	class BasicString
	{
	public:
		/**
		 * Define a iterator to iterate through the data.
		 */
		using Iterator = Char*;

		/**
		 * Define a const iterator to iterate through the data.
		 */
		using ConstIterator = const Char*;

		/**
		 * Define a public typedef for char type used in this class.
		 */
		using CharType = Char;

		/**
		 * Define a public typedef for value type used in this class.
		 */
		using ValueType = Char;

	private:
		Char* data;
		uint32 size;
		uint32 capacity;

	public:
		BasicString() noexcept;

		BasicString(uint32 capacity) noexcept;

		BasicString(const Char* const data) noexcept;

		BasicString(const BasicString& other) noexcept;

#if defined(FMATIO_MOVE_SEMANTICS_ENABLED) && FMATIO_MOVE_SEMANTICS_ENABLED == 1
		BasicString(BasicString&& other) noexcept;
#endif

		~BasicString() noexcept;

	private:
		void initialize(uint32 capacity) noexcept;

		void reallocate(uint32 newCapacity) noexcept;

		void copy(const Char* const data, uint32 size) noexcept;

		void deallocate() noexcept;

	public:
		const Char* getData() const noexcept;

		uint32 getSize() const noexcept;

		uint32 getCapacity() const noexcept;

		bool isEmpty() const noexcept;

		void append(const Char* const string) noexcept;

		void append(const Char* const begin, uint32 size) noexcept;

		void clear() noexcept;

		Char* getBegin() noexcept;

		Char* getEnd() noexcept;

		const Char* getConstBegin() const noexcept;

		const Char* getConstEnd() const noexcept;

	public:
		BasicString& operator =(const BasicString& other) noexcept;

#if defined(FMATIO_MOVE_SEMANTICS_ENABLED) && FMATIO_MOVE_SEMANTICS_ENABLED == 1
		BasicString& operator =(BasicString&& other) noexcept;
#endif

		bool operator ==(const BasicString& other) const noexcept;

		bool operator !=(const BasicString& other) const noexcept;

		Char& operator [](uint32 index) noexcept;

		const Char& operator [](uint32 index) const noexcept;
	};
#pragma endregion

	namespace details
	{
#pragma region Writers
		/**
		 * Format writer inteface that provides 'write' method.
		 * 
		 * @tparam Char
		 * 		Char type for the writer.
		 */
		template<typename Char>
		class BasicFormatWriter
		{
		public:
			/**
			 * Destroy the basic format writer object.
			 */
			virtual ~BasicFormatWriter() noexcept;

		public:
			/**
			 * Write / append stringified fromat argument to the string.
			 * 
			 * @param[in] stringified
			 * 		Stringified format argument value.
			 */
			virtual void write(BasicStringView<Char> stringified) noexcept = 0;
		};

		/**
		 * A dynamic writer that appends format arguments' values.
		 * 
		 * @tparam Container
		 * 		A container in which stringified arguments are written type.
		 */
		template<typename Container>
		class BasicDynamicWriter : public BasicFormatWriter<typename Container::CharType>
		{
		private:
			Container& container;

		public:
			/**
			 * Construct a new basic dynamic writer object.
			 * 
			 * @param[in] container
			 * 		A container in which stringified arguments are written.
			 */
			BasicDynamicWriter(Container& container) noexcept;

			/**
			 * Destroy the basic dynamic writer object.
			 */
			virtual ~BasicDynamicWriter() noexcept override;

		public:
			/**
			 * Write / append stringified fromat argument to the string.
			 * 
			 * @param[in] stringified
			 * 		Stringified format argument value.
			 */
			virtual void write(BasicStringView<typename Container::CharType> stringified) noexcept override;
		};
#pragma endregion

#pragma region Types Writers
		template<typename Char>
		void int8Handle(BasicFormatWriter<Char>& writer, int8 value) noexcept
		{
			::std::string string = ::std::to_string(value);	// Have to reimplement this!
			writer.write(BasicStringView<Char>(string.data()));
		}

		template<typename Char>
		void uint8Handle(BasicFormatWriter<Char>& writer, uint8 value) noexcept
		{
			::std::string string = ::std::to_string(value);	// Have to reimplement this!
			writer.write(BasicStringView<Char>(string.data()));
		}

		template<typename Char>
		void int16Handle(BasicFormatWriter<Char>& writer, int16 value) noexcept
		{
			::std::string string = ::std::to_string(value);	// Have to reimplement this!
			writer.write(BasicStringView<Char>(string.data()));
		}

		template<typename Char>
		void uint16Handle(BasicFormatWriter<Char>& writer, uint16 value) noexcept
		{
			::std::string string = ::std::to_string(value);	// Have to reimplement this!
			writer.write(BasicStringView<Char>(string.data()));
		}

		template<typename Char>
		void int32Handle(BasicFormatWriter<Char>& writer, int32 value) noexcept
		{
			::std::string string = ::std::to_string(value);	// Have to reimplement this!
			writer.write(BasicStringView<Char>(string.data()));
		}

		template<typename Char>
		void uint32Handle(BasicFormatWriter<Char>& writer, uint32 value) noexcept
		{
			::std::string string = ::std::to_string(value);	// Have to reimplement this!
			writer.write(BasicStringView<Char>(string.data()));
		}

		template<typename Char>
		void int64Handle(BasicFormatWriter<Char>& writer, int64 value) noexcept
		{
			::std::string string = ::std::to_string(value);	// Have to reimplement this!
			writer.write(BasicStringView<Char>(string.data()));
		}

		template<typename Char>
		void uint64Handle(BasicFormatWriter<Char>& writer, uint64 value) noexcept
		{
			::std::string string = ::std::to_string(value);	// Have to reimplement this!
			writer.write(BasicStringView<Char>(string.data()));
		}

		template<typename Char>
		void floatHandle(BasicFormatWriter<Char>& writer, float value) noexcept
		{
			::std::string string = ::std::to_string(value);	// Have to reimplement this!
			writer.write(BasicStringView<Char>(string.data()));
		}

		template<typename Char>
		void doubleHandle(BasicFormatWriter<Char>& writer, double value) noexcept
		{
			::std::string string = ::std::to_string(value);	// Have to reimplement this!
			writer.write(BasicStringView<Char>(string.data()));
		}

		template<typename Char>
		void charStringHandle(BasicFormatWriter<Char>& writer, char* value) noexcept
		{
			writer.write(BasicStringView<Char>(value));
		}

		template<typename Char>
		void charStringHandle(BasicFormatWriter<Char>& writer, const char* value) noexcept
		{
			writer.write(BasicStringView<Char>(value));
		}
#pragma endregion

#pragma region Arguments
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
#pragma endregion
	}

#pragma region Format
	template<typename Char>
	void formatHandle(details::BasicFormatWriter<Char>& writer, BasicStringView<Char> pattern, const details::BasicFormatArgumentsList<Char>& arguments) noexcept;

	template<typename Result, typename Pattern, typename... Arguments>
	Result format(const Pattern& pattern, Arguments&&... arguments) noexcept;

	template<typename Pattern, typename... Arguments>
	BasicString<char> format(const Pattern& pattern, Arguments&&... arguments) noexcept;

	template<typename Pattern, typename... Arguments>
	BasicString<wchar> wformat(const Pattern& pattern, Arguments&&... arguments) noexcept;

	template<typename Stream, typename Pattern, typename... Arguments>
	void echo(Stream& stream, const Pattern& pattern, Arguments&&... arguments) noexcept;
#pragma endregion

#pragma region Std Utils
	template<typename Char = char>
	::std::ostream& operator <<(::std::ostream& stream, const fmatio::BasicString<Char>& string) noexcept
	{
		stream << string.getData();
		return stream;
	}

	template<typename Char>
	::std::basic_string<Char> toStdBasicString(const fmatio::BasicString<Char>& string) noexcept
	{
		return ::std::basic_string<Char>(string.getData(), string.getSize());
	}

	template<typename Char = char>
	::std::ostream& operator <<(::std::ostream& stream, const fmatio::BasicStringView<Char>& stringView) noexcept
	{
		stream << stringView.getData();
		return stream;
	}

	template<typename Char>
	::std::basic_string<Char> toStdBasicString(const fmatio::BasicStringView<Char>& stringView) noexcept
	{
		return ::std::basic_string<Char>(stringView.getData(), stringView.getSize());
	}
#pragma endregion
}

namespace fmatio
{
#pragma region BasicStringView
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
#pragma endregion

#pragma region BasicString
	template<typename Char>
	BasicString<Char>::BasicString() noexcept
		: data(), size(), capacity() {
		initialize(8);
	}

	template<typename Char>
	BasicString<Char>::BasicString(uint32 capacity) noexcept
		: data(), size(), capacity() {
		initialize(capacity);
	}

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
		: data(other.data), size(other.size), capacity(other.capacity) {
		other.data = nullptr;
	}
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
#pragma endregion

	namespace details
	{
#pragma region Writers
		template<typename Char>
		BasicFormatWriter<Char>::~BasicFormatWriter() noexcept { };

		template<typename Container>
		BasicDynamicWriter<Container>::BasicDynamicWriter(Container& container) noexcept
			: container(container) { }

		template<typename Container>
		BasicDynamicWriter<Container>::~BasicDynamicWriter() noexcept { }

		template<typename Container>
		void BasicDynamicWriter<Container>::write(BasicStringView<typename Container::CharType> stringified) noexcept
		{
			this->container.append(stringified.getData(), stringified.getSize());
		}
#pragma endregion

#pragma region Arguments
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
				charStringHandle(writer, *static_cast<char* const *>(this->value));
				break;

			case FormatArgumentType::ConstCharString:
				charStringHandle(writer, *static_cast<const char* const *>(this->value));
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

			if (type != FormatArgumentType::Unknown)
			{
				return BasicFormatArgument<Char>(type, &value);
			}
			else if (::std::is_pointer_v<Value>)
			{
				return BasicFormatArgument<Char>(FormatArgumentType::VoidPointer, &value);
			}
			
			return BasicFormatArgument<Char>();
		}
#pragma endregion
	}

#pragma region Format
	template<typename Char>
	void formatHandle(details::BasicFormatWriter<Char>& writer, BasicStringView<Char> pattern, const details::BasicFormatArgumentsList<Char>& arguments) noexcept
	{
		uint32 count = 0;

		for (BasicStringView<Char>::ConstIterator it = pattern.getConstBegin(); it != pattern.getConstEnd(); it++)
			if (*it == '{' && *(it + 1) == '}')
				count++;

		FMATIO_ASSERT(count == arguments.getSize(), "Format arguments count and their placeholders \'{}\' count are different!");
		uint32 index = 0;

		for (BasicStringView<Char>::ConstIterator it = pattern.getConstBegin(); it != pattern.getConstEnd(); it++)
		{
			if (*it == '{' && *(it + 1) == '}' && index <= pattern.getSize())
			{
				arguments.format(writer, index++); it++;
			}
			else
			{
				writer.write(BasicStringView<Char>(it, 1));
			}
		}

		writer.write(BasicStringView<Char>((char*)"\0", 1));
	}

	template<typename Result, typename Pattern, typename... Arguments>
	Result format(const Pattern& pattern, Arguments&&... arguments) noexcept
	{
		using CharType = Result::CharType; Result result = Result();
		details::BasicDynamicWriter<Result> writer = details::BasicDynamicWriter<Result>(result);
		formatHandle(writer, BasicStringView<CharType>(pattern), { details::makeFormatArgument<CharType>(arguments)... });
		FMATIO_ASSERT(result.getData() != nullptr && result.getSize() > 0, "Format resulted in a invalid string!");
		return result;
	}

	template<typename Pattern, typename... Arguments>
	BasicString<char> format(const Pattern& pattern, Arguments&&... arguments) noexcept
	{
		BasicString<char> result = format<BasicString<char>, Pattern, Arguments...>(pattern, ::std::forward<Arguments>(arguments)...);
		return result;
	}

	template<typename Pattern, typename... Arguments>
	BasicString<wchar> wformat(const Pattern& pattern, Arguments&&... arguments) noexcept
	{
		BasicString<wchar> result = format<BasicString<wchar>, Pattern, Arguments...>(pattern, ::std::forward<Arguments>(arguments)...);
		return result;
	}

	template<typename Stream, typename Pattern, typename... Arguments>
	void echo(Stream& stream, const Pattern& pattern, Arguments&&... arguments) noexcept
	{
		stream << format<Pattern, Arguments...>(pattern, ::std::forward<Arguments>(arguments)...).getData();
	}
#pragma endregion
}

#endif
