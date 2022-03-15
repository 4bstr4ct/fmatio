/*******************************************************************************
 * @file core.hpp
 *
 * @author Joris Baranauskas (jorisb)
 *
 * Defines macros and helper utilities.
 *
 * @copyright © 2022-2023 by Joris Baranauskas
 *
 * This file is distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.
 * You should have received a copy of the license along with this project.
 * If not, see https://www.gnu.org/licenses/.
 ******************************************************************************/

#ifndef FMATIO_INCLUDE_FMATIO_CORE_HPP
#define FMATIO_INCLUDE_FMATIO_CORE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#	pragma once
#endif

#ifndef FMATIO_CLANG_VERSION
#	if defined(__clang__) && !defined(__ibmxl__)
#		define FMATIO_CLANG_VERSION (__clang_major__ * 100 + __clang_minor__)
#	else
#		define FMATIO_CLANG_VERSION 0
#	endif
#endif

#ifndef FMATIO_GCC_VERSION
#	if defined(__GNUC__) && !defined(__clang__) && !defined(__INTEL_COMPILER) && !defined(__NVCOMPILER)
#		define FMATIO_GCC_VERSION (__GNUC__ * 100 + __GNUC_MINOR__)
#	else
#		define FMATIO_GCC_VERSION 0
#	endif
#endif

#ifndef FMATIO_GCC_PRAGMA
#	if FMATIO_GCC_VERSION >= 504
#		define FMATIO_GCC_PRAGMA(arg) _Pragma(arg)
#	else
#		define FMATIO_GCC_PRAGMA(arg)
#	endif
#endif

#ifndef FMATIO_ICC_VERSION
#	ifdef __ICL
#		define FMATIO_ICC_VERSION __ICL
#	elif defined(__INTEL_COMPILER)
#		define FMATIO_ICC_VERSION __INTEL_COMPILER
#	else
#		define FMATIO_ICC_VERSION 0
#	endif
#endif

#ifndef FMATIO_NVCOMPILER_VERSION
#	ifdef __NVCOMPILER
#		define FMATIO_NVCOMPILER_VERSION (__NVCOMPILER_MAJOR__ * 100 + __NVCOMPILER_MINOR__)
#	else
#		define FMATIO_NVCOMPILER_VERSION 0
#	endif
#endif

#ifndef FMATIO_NVCC
#	ifdef __NVCC__
#		define FMATIO_NVCC __NVCC__
#	else
#		define FMATIO_NVCC 0
#	endif
#endif

#ifndef FMATIO_MSC_VER
#	ifdef _MSC_VER
#		define FMATIO_MSC_VER _MSC_VER
#	else
#		define FMATIO_MSC_VER 0
#	endif
#endif

#ifndef FMATIO_MSC_WARNING
#	ifdef _MSC_VER
#		define FMATIO_MSC_WARNING(...) __pragma(warning(__VA_ARGS__))
#	else
#		define FMATIO_MSC_WARNING(...)
#	endif
#endif

#ifndef FMATIO_HAS_FEATURE
#	ifdef __has_feature
#		define FMATIO_HAS_FEATURE(x) __has_feature(x)
#	else
#		define FMATIO_HAS_FEATURE(x) 0
#	endif
#endif

#ifndef FMATIO_CPLUSPLUS
#	ifdef _MSVC_LANG
#		define FMATIO_CPLUSPLUS _MSVC_LANG
#	else
#		define FMATIO_CPLUSPLUS __cplusplus
#	endif
#endif

#ifndef FMATIO_HAS_CPP_ATTRIBUTE
#	ifdef __has_cpp_attribute
#		define FMATIO_HAS_CPP_ATTRIBUTE(x) __has_cpp_attribute(x)
#	else
#		define FMATIO_HAS_CPP_ATTRIBUTE(x) 0
#	endif
#endif

#ifndef FMATIO_HAS_CPP14_ATTRIBUTE
#	define FMATIO_HAS_CPP14_ATTRIBUTE(attribute) \
		(FMATIO_CPLUSPLUS >= 201402L && FMATIO_HAS_CPP_ATTRIBUTE(attribute))
#endif

#ifndef FMATIO_HAS_CPP17_ATTRIBUTE
#	define FMATIO_HAS_CPP17_ATTRIBUTE(attribute) \
		(FMATIO_CPLUSPLUS >= 201703L && FMATIO_HAS_CPP_ATTRIBUTE(attribute))
#endif

#ifndef FMATIO_MOVE_SEMANTICS_ENABLED
#	if defined(FMATIO_CLANG_VERSION)
#		if FMATIO_HAS_FEATURE(__cxx_rvalue_references__)
#			define FMATIO_MOVE_SEMANTICS_ENABLED 1
#		endif
#	endif
#	if defined(__GNUC__)
#		if ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 8)) || (__GNUC__ > 4)
#			if (FMATIO_CPLUSPLUS >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#				define FMATIO_MOVE_SEMANTICS_ENABLED 1
#			endif
#		endif
#	endif
#	if defined(FMATIO_MSC_VER) && (FMATIO_MSC_VER >= 1700)
#		define FMATIO_MOVE_SEMANTICS_ENABLED 1
#	endif
#	if defined(__INTEL_CXX11_MODE__)
#		if defined(FMATIO_ICC_VERSION) && (FMATIO_ICC_VERSION >= 1500)
#			define FMATIO_MOVE_SEMANTICS_ENABLED 1
#		endif
#	endif
#endif

#ifndef FMATIO_USE_CONSTEXPR
#	define FMATIO_USE_CONSTEXPR (FMATIO_HAS_FEATURE(cxx_relaxed_constexpr) || FMATIO_MSC_VER >= 1912 || (FMATIO_GCC_VERSION >= 600 && __cplusplus >= 201402L)) && !FMATIO_NVCC && !FMATIO_ICC_VERSION
#endif

#ifdef FMATIO_USE_CONSTEXPR
#	if FMATIO_USE_CONSTEXPR
#		define FMATIO_CONSTEXPR constexpr
#		define FMATIO_CONSTEXPR_DECL constexpr
#	else
#		define FMATIO_CONSTEXPR
#		define FMATIO_CONSTEXPR_DECL
#	endif
#endif

#ifndef FMATIO_NOEXCEPT
#	if defined(_MSC_VER) && (_MSC_VER < 1900)
#		define FMATIO_NOEXCEPT _NOEXCEPT
#	else
#		define FMATIO_NOEXCEPT noexcept
#	endif
#endif

#ifndef FMATIO_INLINE
# 	if FMATIO_GCC_VERSION || FMATIO_CLANG_VERSION
#		define FMATIO_INLINE inline __attribute__((always_inline))
#	else
#		define FMATIO_INLINE inline
#	endif
#endif

#ifndef FMATIO_NOINLINE
#	if FMATIO_GCC_VERSION || FMATIO_CLANG_VERSION
#		define FMATIO_NOINLINE __attribute__((noinline))
#	else
#		define FMATIO_NOINLINE
#	endif
#endif

#ifndef FMATIO_NORETURN
#	if FMATIO_EXCEPTIONS && FMATIO_HAS_CPP_ATTRIBUTE(noreturn) && !FMATIO_MSC_VER && !FMATIO_NVCC
#		define FMATIO_NORETURN [[noreturn]]
#	else
#		define FMATIO_NORETURN
#	endif
#endif

#ifndef FMATIO_NODISCARD
#	if FMATIO_HAS_CPP17_ATTRIBUTE(nodiscard)
#		define FMATIO_NODISCARD [[nodiscard]]
#	else
#		define FMATIO_NODISCARD
#	endif
#endif

#ifndef FMATIO_DEPRECATED
#	if FMATIO_HAS_CPP14_ATTRIBUTE(deprecated) || FMATIO_MSC_VER >= 1900
#		define FMATIO_DEPRECATED [[deprecated]]
#	else
#		if (defined(__GNUC__) && !defined(__LCC__)) || defined(__clang__)
#			define FMATIO_DEPRECATED __attribute__((deprecated))
#		elif FMATIO_MSC_VER
#			define FMATIO_DEPRECATED __declspec(deprecated)
#		else
#			define FMATIO_DEPRECATED /* deprecated */
#		endif
#	endif
#endif

#ifndef FMATIO_DEBUG
#	define FMATIO_DEBUG NDEBUG
#endif

#ifndef FMATIO_ASSERT
#	ifdef FMATIO_DEBUG

#include <iostream>

namespace fmatio
{
	namespace exceptions
	{
		template<typename Condition, typename Message, typename File, typename Line>
		FMATIO_CONSTEXPR FMATIO_INLINE void fmatioAssert(Condition condition, Message message, File file, Line line)
		{
			if (!(condition))
			{
				::std::cerr << "Assertion failed: " << message << "\n\tFile: " << __FILE__ << ". Line: " << __LINE__ << "." << ::std::endl;
				throw;
			}
		}
	}
}

#		define FMATIO_ASSERT(condition, message) \
			::fmatio::exceptions::fmatioAssert<bool, const char* const, const char* const, unsigned int>(condition, message, __FILE__, (unsigned int)__LINE__);

#		define FMATIO_STATIC_ASSERT(condition, message) \
			static_assert(condition, message);
#	else
#		define FMATIO_ASSERT(condition, message)
#	endif
#endif

#ifndef FMATIO_OS
#	ifndef FMATIO_OS_WINDOWS
#		if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#			define FMATIO_OS_WINDOWS 1
#			define FMATIO_OS FMATIO_OS_WINDOWS
#		endif
#		ifdef _WIN64
#			define FMATIO_OS_WINDOWS_X64 1
#		else
#			define FMATIO_OS_WINDOWS_X32 1
#		endif
#	endif
#	ifndef FMATIO_OS_LINUX
#		if __linux__
#			define FMATIO_OS_LINUX 1
#			define FMATIO_OS FMATIO_OS_LINUX
#		endif
#	endif
#	ifndef FMATIO_OS_MACOS
#		if __APPLE__
#			define FMATIO_OS_MACOS 1
#			define FMATIO_OS FMATIO_OS_MACOS
#		endif
#	endif
#endif

#endif
