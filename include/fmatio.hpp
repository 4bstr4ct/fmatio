/*******************************************************************************
 * @file fmatio.hpp
 * 
 * @author Joris Baranauskas (jorisb)
 * 
 * Main library header. It includes most often used and important
 * headers and defines main library methods.
 * 
 * @copyright © 2022-2023 by Joris Baranauskas
 * 
 * This file are distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.
 * You should have received a copy of the license along with this project.
 * If not, see https://www.gnu.org/licenses/.
 ******************************************************************************/

#ifndef FMATIO_INCLUDE_FMATIO_HPP
#define FMATIO_INCLUDE_FMATIO_HPP

#include <fmatio/core.hpp>
#include <fmatio/string_view.hpp>

#include <memory>
#include <sstream>
#include <string>
#include <string_view>

namespace fmatio
{
	FMATIO_API class Argument
	{
	public:
		const char* const format() const
		{
			return "argument";
		}

	public:
		bool operator ==(const Argument& other) const
		{
			return true;
		}

		bool operator !=(const Argument& other) const
		{
			return !(*this == other);
		}
	};

	template<typename... Args>
	FMATIO_API class ArgumentsList
	{
	private:
		/**
		 * A linked list node that holds argument and pointers to
		 * previous and next nodes.
		 */
		struct Node
		{
		public:
			Node* previous;
			Node* next;
			Argument argument;
		};

	private:
		Node* head;
		Node* tail;
		uint32 size;

	public:
		ArgumentsList()
			: head(), tail(), size()
		{
		}

		ArgumentsList(Args&&... args)
			: head(), tail(), size()
		{
			for (uint32 i = 0; i < sizeof...(args); i++)
				this->enqueue(Argument());
		}

		ArgumentsList(const ArgumentsList& other)
			: head(), tail(), size()
		{
			Node* iterator = other.head;

			while (iterator != nullptr)
			{
				this->enqueue(iterator->argument);
				iterator = iterator->next;
			}
		}

#if defined(FMATIO_MOVE_SEMANTICS_ENABLED) && FMATIO_MOVE_SEMANTICS_ENABLED == 1
		ArgumentsList(ArgumentsList&& other)
			: head(other.head), tail(other.tail), size(other.size)
		{
			other.head = nullptr;
			other.tail = nullptr;
		}
#endif

		~ArgumentsList()
		{
			this->clear();
		}

	public:
		uint32 getSize() const { return this->size; }

		bool isEmpty() const { return this->size <= 0; }

		bool isNotEmpty() const { return this->size > 0; }

		const Argument& peek() const
		{
			// ASSERT(this->head != nullptr, "Failed to peek an empty queue!");
			return this->head->argument;
		}

		Argument dequeue()
		{
			// ASSERT(this->head != nullptr, "Failed to dequeue from empty queue!");
			Argument first = this->head->argument;
			Node* temp = this->head;
			this->head = this->head->next;
			delete temp;
			this->size--;
			return first;
		}

		void enqueue(const Argument& item)
		{
			Node* temp = new Node{ this->tail, nullptr, item };

			if (this->head == nullptr)
			{
				this->head = temp;
				this->tail = this->head;
			}
			else
			{
				this->tail->next = temp;
				this->tail = this->tail->next;
			}

			this->size++;
		}

#if defined(FMATIO_MOVE_SEMANTICS_ENABLED) && FMATIO_MOVE_SEMANTICS_ENABLED == 1
		void enqueue(Argument&& item)
		{
			Node* temp = new Node{ this->tail, nullptr, ::std::move(item) };

			if (this->head == nullptr)
			{
				this->head = temp;
				this->tail = this->head;
			}
			else
			{
				this->tail->next = temp;
				this->tail = this->tail->next;
			}

			this->size++;
		}
#endif

#if defined(FMATIO_MOVE_SEMANTICS_ENABLED) && FMATIO_MOVE_SEMANTICS_ENABLED == 1
		template<typename... Args>
		Argument& enqueue(Args&&... args)
		{
			Node* temp = new Node{ this->tail, nullptr, Argument(::std::forward<Args>(args)...) };

			if (this->head == nullptr)
			{
				this->head = temp;
				this->tail = this->head;
			}
			else
			{
				this->tail->next = temp;
				this->tail = this->tail->next;
			}

			this->size++;
			return this->tail->argument;
		}
#endif

		void clear()
		{
			Node* iterator = this->head;
			Node* temp = nullptr;

			while (iterator != nullptr)
			{
				temp = iterator->next;
				delete iterator;
				iterator = temp;
			}

			this->head = nullptr;
			this->tail = nullptr;
			this->size = 0;
		}

	public:
		ArgumentsList& operator =(const ArgumentsList& other)
		{
			this->clear();
			Node* iterator = other.head;

			while (iterator != nullptr)
			{
				this->enqueue(iterator->argument);
				iterator = iterator->next;
			}

			return *this;
		}

#if defined(FMATIO_MOVE_SEMANTICS_ENABLED) && FMATIO_MOVE_SEMANTICS_ENABLED == 1
		ArgumentsList& operator =(ArgumentsList&& other)
		{
			if (this == &other)
				return *this;

			this->clear();
			this->head = other.head;
			other.head = nullptr;
			this->tail = other.tail;
			other.tail = nullptr;
			this->size = other.size;
			return *this;
		}
#endif

		bool operator ==(const ArgumentsList& other) const
		{
			if (this == &other)
				return true;

			if (this->size != other.size)
				return false;

			// ASSERT(this->head != nullptr, "Failed to compare with an empty queue!");
			// ASSERT(other.head != nullptr, "Failed to compare with an empty queue!");

			Node* thisIterator = this->head;
			Node* otherIterator = other.head;

			while (thisIterator != nullptr && otherIterator != nullptr)
			{
				if (thisIterator->argument != otherIterator->argument)
					return false;

				thisIterator = thisIterator->next;
				otherIterator = otherIterator->next;
			}

			return true;
		}

		bool operator !=(const ArgumentsList& other) const
		{
			return !(*this == other);
		}

	public:
		static ArgumentsList create()
		{
			return ArgumentsList();
		}

		static ArgumentsList create(const Argument* const data, uint32 size)
		{
			return ArgumentsList(data, size);
		}

		static bool equals(const ArgumentsList& a, const ArgumentsList& b)
		{
			return a == b;
		}
	};

	template<typename... Args>
	FMATIO_API class Formatter
	{
	private:
		StringView pattern;
		ArgumentsList<Args&&...> argumentsList;

	public:
		Formatter(const StringView& pattern, const ArgumentsList<Args&&...>& argumentsList)
			: pattern(pattern), argumentsList(argumentsList) { }

		~Formatter() { }

	public:
		::std::string format()
		{
			using StringStream = ::std::stringstream;
			StringStream stream = StringStream();

			uint32 count = 0;
			for (StringView::Iterator it = this->pattern.getBegin(); it != this->pattern.getEnd(); it++)
				if (*it == '{' && *(it + 1) == '}')
					count++;

			if (count != this->argumentsList.getSize())
				::std::exit(-9);

			for (StringView::Iterator it = this->pattern.getBegin(); it != this->pattern.getEnd(); it++)
			{
				if (*it == '{')
				{
					Argument argument = this->argumentsList.dequeue();
					stream << argument.format();
				}
				else if (*it == '}')
				{
					continue;
				}
				else
				{
					stream << *it;
				}
			}

			return stream.str();
		}
	};





	template<typename>
	FMATIO_API ::std::string format(const StringView& pattern) noexcept;

	template<typename... Args>
	FMATIO_API ::std::string format(const StringView& pattern, Args&&... args) noexcept;

	template<typename Stream, typename... Args>
	FMATIO_API void echo(Stream& stream, const StringView& pattern, Args&&... args) noexcept;

	template<typename... Args>
	FMATIO_API void print(const StringView& pattern, Args&&... args) noexcept;
}

#include "../source/fmatio.inl"

#endif
