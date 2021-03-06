/*******************************************************************************
 * @file types.hpp
 * 
 * @author Joris Baranauskas (jorisb)
 * 
 * Defines primitive types.
 * 
 * @copyright © 2022-2023 by Joris Baranauskas
 * 
 * This file is distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.
 * You should have received a copy of the license along with this project.
 * If not, see https://www.gnu.org/licenses/.
 ******************************************************************************/

#ifndef FMATIO_INCLUDE_FMATIO_TYPES_HPP
#define FMATIO_INCLUDE_FMATIO_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#	pragma once
#endif

namespace fmatio
{
	/**
	 * A type represeting null pointer
	 */
	using null = decltype(nullptr);

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
}

#endif
