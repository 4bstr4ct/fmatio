cmake_minimum_required(VERSION 3.3)
project("fmatio" LANGUAGES C CXX)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
	cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

if(NOT DEFINED FMATIO_IS_MASTER_PROJECT)
	set(FMATIO_IS_MASTER_PROJECT OFF)

	if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
		set(FMATIO_IS_MASTER_PROJECT ON)
		message(STATUS "CMake version: ${CMAKE_VERSION}")
	endif()
endif()

function(join result_var)
	set(result "")

	foreach(arg ${ARGN})
		set(result "${result}${arg}")
	endforeach()

	set(${result_var} "${result}" PARENT_SCOPE)
endfunction()

include(CMakeParseArguments)

function(set_verbose)
	list(GET ARGN 0 var)
	list(REMOVE_AT ARGN 0)
	list(GET ARGN 0 val)
	list(REMOVE_AT ARGN 0)
	list(REMOVE_AT ARGN 0)
	list(GET ARGN 0 type)
	list(REMOVE_AT ARGN 0)
	join(doc ${ARGN})
	set(${var} ${val} CACHE ${type} ${doc})
endfunction()

if(FMATIO_IS_MASTER_PROJECT AND NOT CMAKE_BUILD_TYPE)
	set_verbose(CMAKE_BUILD_TYPE Release CACHE STRING
				"Choose the type of build, options are: None(CMAKE_CXX_FLAGS or "
				"CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
endif()

if(FMATIO_IS_MASTER_PROJECT AND NOT DEFINED CMAKE_CXX_VISIBILITY_PRESET)
	set_verbose(CMAKE_CXX_VISIBILITY_PRESET hidden CACHE STRING
				"Preset for the export of private symbols")
	set_property(CACHE CMAKE_CXX_VISIBILITY_PRESET PROPERTY STRINGS
				hidden default)
endif()

if(FMATIO_IS_MASTER_PROJECT AND NOT DEFINED CMAKE_VISIBILITY_INLINES_HIDDEN)
	set_verbose(CMAKE_VISIBILITY_INLINES_HIDDEN ON CACHE BOOL
				"Whether to add a compile flag to hide symbols of inline functions")
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
	set(PEDANTIC_COMPILE_FLAGS -pedantic-errors -Wall -Wextra -pedantic
		-Wold-style-cast -Wundef
		-Wredundant-decls -Wwrite-strings -Wpointer-arith
		-Wcast-qual -Wformat=2 -Wmissing-include-dirs
		-Wcast-align
		-Wctor-dtor-privacy -Wdisabled-optimization
		-Winvalid-pch -Woverloaded-virtual
		-Wconversion -Wundef
		-Wno-ctor-dtor-privacy -Wno-format-nonliteral)

	if(NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.6)
		set(PEDANTIC_COMPILE_FLAGS ${PEDANTIC_COMPILE_FLAGS}
			-Wno-dangling-else -Wno-unused-local-typedefs)
	endif()

	if(NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 5.0)
		set(PEDANTIC_COMPILE_FLAGS ${PEDANTIC_COMPILE_FLAGS} -Wdouble-promotion
			-Wtrampolines -Wzero-as-null-pointer-constant -Wuseless-cast
			-Wvector-operation-performance -Wsized-deallocation -Wshadow)
	endif()

	if(NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 6.0)
		set(PEDANTIC_COMPILE_FLAGS ${PEDANTIC_COMPILE_FLAGS} -Wshift-overflow=2
			-Wnull-dereference -Wduplicated-cond)
	endif()
	
	set(WERROR_FLAG -Werror)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	set(PEDANTIC_COMPILE_FLAGS -Wall -Wextra -pedantic -Wconversion -Wundef
		-Wdeprecated -Wweak-vtables -Wshadow
		-Wno-gnu-zero-variadic-macro-arguments)
		# check_cxx_compiler_flag(-Wzero-as-null-pointer-constant HAS_NULLPTR_WARNING)

	if(HAS_NULLPTR_WARNING)
		set(PEDANTIC_COMPILE_FLAGS ${PEDANTIC_COMPILE_FLAGS}
			-Wzero-as-null-pointer-constant)
	endif()

	set(WERROR_FLAG -Werror)
endif()

if(MSVC)
	set(PEDANTIC_COMPILE_FLAGS /W3)
	set(WERROR_FLAG /WX)
endif()

set(FMATIO_EXTERNAL_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/external")
set(FMATIO_INCLUDE_DIRECTORY  "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(FMATIO_SOURCE_DIRECTORY   "${CMAKE_CURRENT_SOURCE_DIR}/source")

file(GLOB FMATIO_INLINE_FILES
	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/format.inl"
	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/basic_string.inl"
	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/basic_string_view.inl"
	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/formatters.inl"

	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/details/arguments.inl"
	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/details/writers.inl"
)

file(GLOB FMATIO_HEADER_FILES
	"${FMATIO_INCLUDE_DIRECTORY}/fmatio.hpp"

	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/core.hpp"
	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/types.hpp"
	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/format.hpp"
	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/basic_string.hpp"
	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/basic_string_view.hpp"
	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/formatters.inl"

	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/details/arguments.hpp"
	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/details/format_traits.hpp"
	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/details/writers.hpp"

	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/details/types/bool.hpp"
	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/details/types/char.hpp"
	
	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/details/types/int8.hpp"
	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/details/types/uint8.hpp"

	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/details/types/int16.hpp"
	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/details/types/uint16.hpp"

	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/details/types/int32.hpp"
	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/details/types/uint32.hpp"

	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/details/types/int64.hpp"
	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/details/types/uint64.hpp"

	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/details/types/float.hpp"
	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/details/types/double.hpp"

	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/details/types/char_string.hpp"
)

set(FMATIO_PUBLIC_HEADER_FILES
	"${FMATIO_INCLUDE_DIRECTORY}/fmatio.hpp"

	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/core.hpp"
	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/types.hpp"
	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/format.hpp"
	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/basic_string.hpp"
	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/basic_string_view.hpp"
	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/formatters.inl"

	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/details/arguments.hpp"
	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/details/format_traits.hpp"
	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/details/writers.hpp"

	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/details/types/bool.hpp"
	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/details/types/char.hpp"

	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/details/types/int8.hpp"
	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/details/types/uint8.hpp"

	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/details/types/int16.hpp"
	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/details/types/uint16.hpp"

	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/details/types/int32.hpp"
	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/details/types/uint32.hpp"

	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/details/types/int64.hpp"
	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/details/types/uint64.hpp"

	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/details/types/float.hpp"
	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/details/types/double.hpp"

	"${FMATIO_INCLUDE_DIRECTORY}/fmatio/details/types/char_string.hpp"
)

set(FMATIO_OS "")

if(WIN32)
	set(FMATIO_OS "FMATIO_OS_WINDOWS")
elseif(UNIX AND NOT APPLE)
	set(FMATIO_OS "FMATIO_OS_LINUX")
elseif(APPLE)
	set(FMATIO_OS "FMATIO_OS_MACOS")
endif()

message(${FMATIO_OS})

string(TOUPPER "${CMAKE_BUILD_TYPE}" BUILD_VARIANT)
set(FMATIO_BUILD_VARIANT "FMATIO_${BUILD_VARIANT}")
message(${FMATIO_BUILD_VARIANT})

add_library(${PROJECT_NAME} INTERFACE)

target_compile_definitions(${PROJECT_NAME}
	INTERFACE
		${FMATIO_BUILD_VARIANT}
		${FMATIO_OS}
		"FMATIO_OS=${FMATIO_OS}"
		"FMATIO_HEADER_ONLY=1"
)

target_include_directories(${PROJECT_NAME}
	INTERFACE
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${FMATIO_INCLUDE_DIRECTORY}>
)

set_target_properties(${PROJECT_NAME} PROPERTIES
	PUBLIC_HEADER "${FMATIO_PUBLIC_HEADER_FILES}"
)

if(FMATIO_TESTS)
	add_subdirectory(tests)
endif()
