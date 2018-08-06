target_sources(${PROJECT_NAME} PUBLIC
	"${CMAKE_CURRENT_LIST_DIR}/edit_common.c"
	"${CMAKE_CURRENT_LIST_DIR}/edit_shape.c"
	"${CMAKE_CURRENT_LIST_DIR}/edit_material.c"
	"${CMAKE_CURRENT_LIST_DIR}/edit_lightsource.c"
	"${CMAKE_CURRENT_LIST_DIR}/edit_texture.c"
	"${CMAKE_CURRENT_LIST_DIR}/scene_mapper.c"

	"${CMAKE_CURRENT_LIST_DIR}/default_position.c"
	"${CMAKE_CURRENT_LIST_DIR}/default_shape.c"
	"${CMAKE_CURRENT_LIST_DIR}/default_primitive.c"
	"${CMAKE_CURRENT_LIST_DIR}/default_material.c"
	"${CMAKE_CURRENT_LIST_DIR}/default_sphere.c"
	"${CMAKE_CURRENT_LIST_DIR}/default_cylinder.c"
	"${CMAKE_CURRENT_LIST_DIR}/default_cone.c"
	"${CMAKE_CURRENT_LIST_DIR}/default_lightsource.c"
	"${CMAKE_CURRENT_LIST_DIR}/default_pointlightsource.c"
	"${CMAKE_CURRENT_LIST_DIR}/default_dirlightsource.c"
	"${CMAKE_CURRENT_LIST_DIR}/default_spotlightsource.c"
)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
