target_sources(${PROJECT_NAME} PUBLIC
	"${CMAKE_CURRENT_LIST_DIR}/upload.c"
	"${CMAKE_CURRENT_LIST_DIR}/camera.c"

	"${CMAKE_CURRENT_LIST_DIR}/load/load.c"
	"${CMAKE_CURRENT_LIST_DIR}/load/load_lightsource.c"
	"${CMAKE_CURRENT_LIST_DIR}/load/load_material.c"
	"${CMAKE_CURRENT_LIST_DIR}/load/load_shape.c"
	"${CMAKE_CURRENT_LIST_DIR}/load/load_primitive.c"

	"${CMAKE_CURRENT_LIST_DIR}/common/vector.c"
	"${CMAKE_CURRENT_LIST_DIR}/common/orientation.c"
	"${CMAKE_CURRENT_LIST_DIR}/common/real.c"
	"${CMAKE_CURRENT_LIST_DIR}/common/color.c"

	"${CMAKE_CURRENT_LIST_DIR}/shape/shape.c"
	"${CMAKE_CURRENT_LIST_DIR}/shape/cone.c"
	"${CMAKE_CURRENT_LIST_DIR}/shape/cylinder.c"
	"${CMAKE_CURRENT_LIST_DIR}/shape/sphere.c"
	"${CMAKE_CURRENT_LIST_DIR}/shape/primitive.c"
	"${CMAKE_CURRENT_LIST_DIR}/shape/material.c"

	"${CMAKE_CURRENT_LIST_DIR}/limitation/limitation.c"
	"${CMAKE_CURRENT_LIST_DIR}/limitation/axial_limitation.c"

	"${CMAKE_CURRENT_LIST_DIR}/lightsource/lightsource.c"
	"${CMAKE_CURRENT_LIST_DIR}/lightsource/pointlightsource.c"
	"${CMAKE_CURRENT_LIST_DIR}/lightsource/dirlightsource.c"
	"${CMAKE_CURRENT_LIST_DIR}/lightsource/spotlightsource.c"
)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
