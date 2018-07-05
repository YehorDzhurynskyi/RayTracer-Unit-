cmake_minimum_required(VERSION 2.8)

project(RT)

# set(CMAKE_VERBOSE_MAKEFILE ON)

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

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/modules/")

### Configuring compiler
if(MSVC)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
	# Default debug flags are OK 
	set(CMAKE_C_FLAGS_RELEASE "{CMAKE_C_FLAGS_RELEASE} /O2")
else()
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")
	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0 -DDEBUG")
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -DNDEBUG")
endif()
###

### Preparing dependecies
find_package(OpenGL REQUIRED)
find_package(OpenCL REQUIRED)
find_package(SDL2 REQUIRED)

include_directories(Dependencies/libft)
add_subdirectory(Dependencies/libft)

add_subdirectory(Dependencies/cson)

add_subdirectory(Dependencies/nuklear)

add_subdirectory(Dependencies/targa)

###

add_executable(${PROJECT_NAME} "")
include(src/CMakeLists.txt)

include_directories(
	${OPENGL_INCLUDE_DIRS}
	${OpenCL_INCLUDE_DIRS}
	${SDL2_INCLUDE_DIRS}
	./include
)

target_link_libraries(${PROJECT_NAME}
	${OPENGL_LIBRARIES}
	${OpenCL_LIBRARIES}
	${SDL2_LIBRARIES}
	ft
	cson
	nuklear
	targa
)
