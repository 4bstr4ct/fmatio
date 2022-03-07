/*******************************************************************************
 * @file core.hpp
 * 
 * @author Joris Baranauskas (jorisb)
 * 
 * Defines macros and helper utilities.
 * 
 * @copyright © 2022-2023 by Joris Baranauskas
 * 
 * This file are distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.
 * You should have received a copy of the license along with this project.
 * If not, see https://www.gnu.org/licenses/.
 ******************************************************************************/

#ifndef FMATIO_INCLUDE_FMATIO_CORE_HPP
#define FMATIO_INCLUDE_FMATIO_CORE_HPP

#define FMATIO_API

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

namespace fmatio { }

#endif