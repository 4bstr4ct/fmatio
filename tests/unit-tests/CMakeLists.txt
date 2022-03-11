cmake_minimum_required(VERSION 3.3.0)
project(unit-tests VERSION 0.0.1 LANGUAGES C CXX)
add_executable(${PROJECT_NAME} main.cpp utils.hpp)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
		fmatio
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC
	PRIVATE
		fmatio
)
