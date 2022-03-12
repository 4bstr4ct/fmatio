/*******************************************************************************
 * @file type_traits.hpp
 *
 * @author Joris Baranauskas (jorisb)
 *
 * Defines classes and utilitites for type traits.
 *
 * @copyright © 2022-2023 by Joris Baranauskas
 *
 * This file is distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.
 * You should have received a copy of the license along with this project.
 * If not, see https://www.gnu.org/licenses/.
 ******************************************************************************/

#ifndef FMATIO_INCLUDE_FMATIO_DETAILS_TYPE_TRAITS_HPP
#define FMATIO_INCLUDE_FMATIO_DETAILS_TYPE_TRAITS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#	pragma once
#endif

#include <fmatio/core.hpp>
#include <fmatio/types.hpp>

namespace fmatio
{
	namespace details
	{
		/**
		 * Remove reference structure.
		 * 
		 * @tparam T
		 * 		Type without reference.
		 */
		template<typename T>
		struct RemoveReference
		{
		public:
			using Type = T;
		};

		/**
		 * Remove reference structure.
		 * 
		 * @tparam T
		 * 		Type with reference.
		 */
		template<typename T>
		struct RemoveReference<T&>
		{
		public:
			using Type = T;
		};

		/**
		 * Remove reference structure.
		 * 
		 * @tparam T
		 * 		Type with double reference.
		 */
		template<typename T>
		struct RemoveReference<T&&>
		{
		public:
			using Type = T;
		};

		/**
		 * Remove reference type structure.
		 * 
		 * @tparam T
		 * 		Type for reference removal.
		 */
		template<typename T>
		using RemoveReferenceType = typename RemoveReference<T>::Type;

		/**
		 * Remove extent structure.
		 * 
		 * @tparam T
		 * 		Type without any extent.
		 */
		template<typename T>
		struct RemoveExtent
		{
		public:
			using Type = T;
		};

		/**
		 * Remove extent structure.
		 * 
		 * @tparam T
		 * 		Type as static array of provided size.
		 * 
		 * @tparam size
		 * 		Size of the array.
		 */
		template<typename T, uint32 size>
		struct RemoveExtent<T[size]>
		{
		public:
			using Type = T;
		};

		/**
		 * Remove extent structure.
		 * 
		 * @tparam T
		 * 		Type as static array.
		 */
		template<typename T>
		struct RemoveExtent<T[]>
		{
		public:
			using Type = T;
		};

		/**
		 * Remove extent type structure.
		 * 
		 * @tparam T
		 * 		Type for extent removal.
		 */
		template<typename T>
		using RemoveExtentType = typename RemoveExtent<T>::Type;

		template<typename T>
		using DecayedIfArray = ::std::conditional_t<::std::is_array_v<T>, RemoveExtentType<T> const*, T>;

		template<typename T>
		using Formattable = DecayedIfArray<RemoveReferenceType<T>>;
	}
}

#endif
