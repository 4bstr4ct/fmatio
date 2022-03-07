/*******************************************************************************
 * @file format_argument.hpp
 * 
 * @author Joris Baranauskas (jorisb)
 * 
 * Defines argument class and helper functions.
 * 
 * @copyright © 2022-2023 by Joris Baranauskas
 * 
 * This file are distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.
 * You should have received a copy of the license along with this project.
 * If not, see https://www.gnu.org/licenses/.
 ******************************************************************************/

#ifndef FMATIO_INCLUDE_FMATIO_ARGS_FORMAT_ARGUMENT_HPP
#define FMATIO_INCLUDE_FMATIO_ARGS_FORMAT_ARGUMENT_HPP

#include <fmatio/core.hpp>

namespace fmatio
{
	class FormatArgument
	{
	private:


	public:
		FormatArgument();

		FormatArgument(const FormatArgument& other);

#if defined(FMATIO_MOVE_SEMANTICS_ENABLED) && FMATIO_MOVE_SEMANTICS_ENABLED == 1
		FormatArgument(FormatArgument&& other);
#endif

		~FormatArgument();
	public:


	public:
		FormatArgument& operator =(const FormatArgument& other);

#if defined(FMATIO_MOVE_SEMANTICS_ENABLED) && FMATIO_MOVE_SEMANTICS_ENABLED == 1
		FormatArgument& operator =(FormatArgument&& other);
#endif

		bool operator ==(const FormatArgument& other) const;

		bool operator !=(const FormatArgument& other) const;

	public:
		static FormatArgument create();
	};
}

#endif
