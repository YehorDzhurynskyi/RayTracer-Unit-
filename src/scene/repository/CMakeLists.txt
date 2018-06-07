target_sources(${PROJECT_NAME} PUBLIC
	"${CMAKE_CURRENT_LIST_DIR}/load.c"
	"${CMAKE_CURRENT_LIST_DIR}/upload.c"

	"${CMAKE_CURRENT_LIST_DIR}/common_deserializer.c"
	"${CMAKE_CURRENT_LIST_DIR}/common_serializer.c"

	"${CMAKE_CURRENT_LIST_DIR}/camera.c"

	"${CMAKE_CURRENT_LIST_DIR}/shape/shape.c"
	"${CMAKE_CURRENT_LIST_DIR}/shape/cone.c"
	"${CMAKE_CURRENT_LIST_DIR}/shape/cylinder.c"
	"${CMAKE_CURRENT_LIST_DIR}/shape/plane.c"
	"${CMAKE_CURRENT_LIST_DIR}/shape/sphere.c"

	"${CMAKE_CURRENT_LIST_DIR}/light/light.c"
	"${CMAKE_CURRENT_LIST_DIR}/light/pointlight.c"
	"${CMAKE_CURRENT_LIST_DIR}/light/dirlight.c"
	"${CMAKE_CURRENT_LIST_DIR}/light/spotlight.c"
)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
