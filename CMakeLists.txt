cmake_minimum_required(VERSION 3.14)
project(ObjectOrientedC)

set(HEADERS
	include/containers/vector.h
	include/containers/common.h)

set(SOURCES
	src/vector.c
)

add_library(containers
	${SOURCES}
	${HEADERS}
)

target_include_directories(containers
	PUBLIC
		include/
)

option(BUILD_CONTAINER_EXAMPLES "Enable building examples in $PROJECT_ROOT/examples" ON)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_CONTAINER_EXAMPLES)
	add_subdirectory(examples)
endif()
