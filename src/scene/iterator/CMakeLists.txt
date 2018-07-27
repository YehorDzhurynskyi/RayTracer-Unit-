target_sources(${PROJECT_NAME} PUBLIC
	"${CMAKE_CURRENT_LIST_DIR}/iter_common.c"
	"${CMAKE_CURRENT_LIST_DIR}/iter_texture.c"
	"${CMAKE_CURRENT_LIST_DIR}/iter_shape.c"
	"${CMAKE_CURRENT_LIST_DIR}/iter_lightsource.c"
	"${CMAKE_CURRENT_LIST_DIR}/iter_material.c"
	"${CMAKE_CURRENT_LIST_DIR}/iter_limitation.c"
)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
