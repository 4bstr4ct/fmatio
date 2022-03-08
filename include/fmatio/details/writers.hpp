/*******************************************************************************
 * @file writers.hpp
 * 
 * @author Joris Baranauskas (jorisb)
 * 
 * Defines various arguments writers.
 * 
 * @copyright © 2022-2023 by Joris Baranauskas
 * 
 * This file are distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.
 * You should have received a copy of the license along with this project.
 * If not, see https://www.gnu.org/licenses/.
 ******************************************************************************/

#ifndef FMATIO_INCLUDE_FMATIO_DETAILS_WRITERS_HPP
#define FMATIO_INCLUDE_FMATIO_DETAILS_WRITERS_HPP

#include <fmatio/core.hpp>
#include <fmatio/string.hpp>
#include <fmatio/string_view.hpp>

namespace fmatio
{
	namespace details
	{
		template<typename Char>
		class BasicFormatWriter
		{
		public:
			virtual ~BasicFormatWriter() noexcept;

		public:
			virtual void write(BasicStringView<Char> string) noexcept = 0;
		};

		template<typename Container>
		class BasicDynamicWriter : public BasicFormatWriter<typename Container::CharType>
		{
		private:
			Container& container;

		public:
			BasicDynamicWriter(Container& container) noexcept;

			virtual ~BasicDynamicWriter() noexcept override;

		public:
			virtual void write(BasicStringView<typename Container::CharType> string) noexcept override;
		};
	}
}

#include "./writers.inl"

#endif
