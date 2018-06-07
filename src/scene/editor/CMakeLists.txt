target_sources(${PROJECT_NAME} PUBLIC
	"${CMAKE_CURRENT_LIST_DIR}/shape.c"
	"${CMAKE_CURRENT_LIST_DIR}/light.c"
	# "${CMAKE_CURRENT_LIST_DIR}/common.c"
)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
