/*******************************************************************************
 * @file writers.hpp
 * 
 * @author Joris Baranauskas (jorisb)
 * 
 * Defines various arguments writers.
 * 
 * @copyright © 2022-2023 by Joris Baranauskas
 * 
 * This file is distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.
 * You should have received a copy of the license along with this project.
 * If not, see https://www.gnu.org/licenses/.
 ******************************************************************************/

#ifndef FMATIO_INCLUDE_FMATIO_DETAILS_WRITERS_HPP
#define FMATIO_INCLUDE_FMATIO_DETAILS_WRITERS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#	pragma once
#endif

#include <fmatio/core.hpp>
#include <fmatio/basic_string_view.hpp>

namespace fmatio
{
	namespace details
	{
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
			virtual ~BasicFormatWriter() FMATIO_NOEXCEPT;

		public:
			/**
			 * Write / append stringified fromat argument to the string.
			 * 
			 * @param[in] stringified
			 * 		Stringified format argument value.
			 */
			virtual void write(BasicStringView<Char> stringified) FMATIO_NOEXCEPT = 0;
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
			BasicDynamicWriter(Container& container) FMATIO_NOEXCEPT;

			/**
			 * Destroy the basic dynamic writer object.
			 */
			virtual ~BasicDynamicWriter() FMATIO_NOEXCEPT override;

		public:
			/**
			 * Write / append stringified fromat argument to the string.
			 * 
			 * @param[in] stringified
			 * 		Stringified format argument value.
			 */
			virtual void write(BasicStringView<typename Container::CharType> stringified) FMATIO_NOEXCEPT override;
		};
	}
}

#include "./writers.inl"

#endif
