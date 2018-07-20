target_sources(${PROJECT_NAME} PUBLIC
	"${CMAKE_CURRENT_LIST_DIR}/common.c"
	"${CMAKE_CURRENT_LIST_DIR}/shape.c"
	"${CMAKE_CURRENT_LIST_DIR}/lightsource.c"
	"${CMAKE_CURRENT_LIST_DIR}/material.c"
	"${CMAKE_CURRENT_LIST_DIR}/limitation.c"
)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
