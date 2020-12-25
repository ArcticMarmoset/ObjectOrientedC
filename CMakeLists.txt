cmake_minimum_required(VERSION 3.14)
project(ObjectOrientedC LANGUAGES C)

set(HEADERS
	include/containers/vector.h
)

set(SOURCES
	src/vector.c
)

add_library(containers
	${SOURCES}
	${HEADERS}
)

option(BUILD_CONTAINER_EXAMPLES "Enable building examples in $PROJECT_ROOT/examples" ON)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_CONTAINER_EXAMPLES)
	include_directories(examples)
endif()
