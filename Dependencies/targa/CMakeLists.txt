cmake_minimum_required(VERSION 2.8)

project(targa)

add_library(${PROJECT_NAME} STATIC
	${CMAKE_CURRENT_LIST_DIR}/targa.c
)

target_include_directories(${PROJECT_NAME} PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)
