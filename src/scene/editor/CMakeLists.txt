target_sources(${PROJECT_NAME} PUBLIC
	"${CMAKE_CURRENT_LIST_DIR}/edit_common.c"
	"${CMAKE_CURRENT_LIST_DIR}/edit_shape.c"
	"${CMAKE_CURRENT_LIST_DIR}/edit_material.c"
	"${CMAKE_CURRENT_LIST_DIR}/edit_lightsource.c"
	"${CMAKE_CURRENT_LIST_DIR}/edit_texture.c"
	"${CMAKE_CURRENT_LIST_DIR}/scene_mapper.c"
)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
