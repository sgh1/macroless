cmake_minimum_required(VERSION 2.6)

#
# (Sorry about this.)
#

project(macroless_test_test)

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
	../macroless.cpp 
	../macroless.h)

include_directories(
	../
)

add_executable(vector_test 
	${SOURCE_FILES}
	std_vector_test.cpp)

add_executable(map_test 
	${SOURCE_FILES}
	std_map_test.cpp)
