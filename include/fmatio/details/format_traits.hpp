/*******************************************************************************
 * @file format_traits.hpp
 *
 * @author Joris Baranauskas (jorisb)
 *
 * Defines classes and utilitites for format traits.
 *
 * @copyright © 2022-2023 by Joris Baranauskas
 *
 * This file is distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.
 * You should have received a copy of the license along with this project.
 * If not, see https://www.gnu.org/licenses/.
 ******************************************************************************/

#ifndef FMATIO_INCLUDE_FMATIO_DETAILS_FORMAT_TRAITS_HPP
#define FMATIO_INCLUDE_FMATIO_DETAILS_FORMAT_TRAITS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#	pragma once
#endif

#include <fmatio/core.hpp>
#include <fmatio/types.hpp>

namespace fmatio
{
	namespace details
	{
		template<typename Char>
		struct FormatTraits;

		template<>
		struct FormatTraits<char>
		{
		public:
			static FMATIO_CONSTEXPR char formatBegin = '{';
			static FMATIO_CONSTEXPR char formatEnd = '}';

			static FMATIO_CONSTEXPR const char trueStringified[] = "true";
			static FMATIO_CONSTEXPR const char falseStringified[] = "false";

			static FMATIO_CONSTEXPR const char nullptrStringified[] = "nullptr";
		};

		template<>
		struct FormatTraits<wchar>
		{
		public:
			static FMATIO_CONSTEXPR wchar formatBegin = L'{';
			static FMATIO_CONSTEXPR wchar formatEnd = L'}';

			static FMATIO_CONSTEXPR const wchar trueStringified[] = L"true";
			static FMATIO_CONSTEXPR const wchar falseStringified[] = L"false";

			static FMATIO_CONSTEXPR const wchar nullptrStringified[] = L"nullptr";
		};
	}
}

#endif
