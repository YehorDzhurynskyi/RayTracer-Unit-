cmake_minimum_required(VERSION 2.8)

project(RT)
set(CMAKE_VERBOSE_MAKEFILE ON)

### Setting output dir
if(NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "Debug") 
	set(CMAKE_BUILD_TYPE Debug)
	set(CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR}/Debug)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
	set(CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR}/Release)
else()
	MESSAGE(SEND_ERROR "Invalid build type: \"" ${CMAKE_BUILD_TYPE}
	"\", this should be \"Debug\"(default) or \"Release\"")
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
###

### Configuring compiler
# set(CMAKE_C_COMPILER "gcc")
set(CMAKE_C_FLAGS_DEBUG "-g -O0")
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_C_FLAGS "-Wall -Werror -Wextra")
###

### Preparing dependecies
find_package(SDL2 REQUIRED)

include_directories(Dependencies/libft)
add_subdirectory(Dependencies/libft)

include_directories(Dependencies/cson)
add_subdirectory(Dependencies/cson)
###

add_executable(${PROJECT_NAME} "")
include(src/CMakeLists.txt)
include_directories(
	${SDL2_INCLUDE_DIRS}
)
target_link_libraries(${PROJECT_NAME}
	${SDL2_LIBRARIES}
	ft
	CSONParser
)
