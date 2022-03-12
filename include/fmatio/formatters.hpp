/*******************************************************************************
 * @file formatters.hpp
 * 
 * @author Joris Baranauskas (jorisb)
 * 
 * Defines various formatters.
 * 
 * @copyright © 2022-2023 by Joris Baranauskas
 * 
 * This file is distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.
 * You should have received a copy of the license along with this project.
 * If not, see https://www.gnu.org/licenses/.
 ******************************************************************************/

#ifndef FMATIO_INCLUDE_FMATIO_FORMATTERS_HPP
#define FMATIO_INCLUDE_FMATIO_FORMATTERS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#	pragma once
#endif

#include <fmatio/core.hpp>
#include <fmatio/types.hpp>
#include <fmatio/basic_string_view.hpp>

#include <fmatio/details/writers.hpp>
#include <fmatio/details/arguments.hpp>

namespace fmatio
{
	template<typename Char>
	class BasicFormatter
	{
	public:
		virtual void format(details::BasicFormatWriter<Char>& writer, BasicStringView<Char> pattern, const details::BasicFormatArgumentsList<Char>& arguments) FMATIO_NOEXCEPT = 0;
	};

	template<typename Char>
	class SafeFmatioFormatter : public BasicFormatter<Char>
	{
	public:
		virtual void format(details::BasicFormatWriter<Char>& writer, BasicStringView<Char> pattern, const details::BasicFormatArgumentsList<Char>& arguments) FMATIO_NOEXCEPT override;
	};
}

#include "./formatters.inl"

#endif
