cmake_minimum_required(VERSION 3.14)
project(ObjectOrientedC)

set(HEADERS
	include/cxx/vector.h
	include/objects/common.h
	include/objects/IVehicle.h
	include/objects/Car.h
	include/objects/Bicycle.h)

set(SOURCES
	src/vector.c
	src/Car.c
	src/Bicycle.c)

add_library(objects
	${SOURCES}
	${HEADERS}
)

target_include_directories(objects
	PUBLIC
		include/
)

option(BUILD_OBJECTS_EXAMPLES "Enable building examples in $PROJECT_ROOT/examples" ON)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_OBJECTS_EXAMPLES)
	add_subdirectory(examples)
endif()
