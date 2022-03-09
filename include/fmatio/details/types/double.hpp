/*******************************************************************************
 * @file double.hpp
 *
 * @author Joris Baranauskas (jorisb)
 *
 * Defines functions to write double.
 *
 * @copyright © 2022-2023 by Joris Baranauskas
 *
 * This file is distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.
 * You should have received a copy of the license along with this project.
 * If not, see https://www.gnu.org/licenses/.
 ******************************************************************************/

#ifndef FMATIO_INCLUDE_FMATIO_DETAILS_TYPES_DOUBLE_HPP
#define FMATIO_INCLUDE_FMATIO_DETAILS_TYPES_DOUBLE_HPP

#include <fmatio/core.hpp>
#include <fmatio/types.hpp>

#include <fmatio/details/writers.hpp>

#include <string>

namespace fmatio
{
	namespace details
	{
		template<typename Char>
		void doubleHandle(BasicFormatWriter<Char>& writer, double value) FMATIO_NOEXCEPT
		{
			::std::string string = ::std::to_string(value);	// Have to reimplement this!
			writer.write(BasicStringView<Char>(string.data()));
		}
	}
}

#endif
