target_sources(${PROJECT_NAME} PUBLIC
	"${CMAKE_CURRENT_LIST_DIR}/intersection/intersection.c"
	"${CMAKE_CURRENT_LIST_DIR}/intersection/sphere.c"
	"${CMAKE_CURRENT_LIST_DIR}/intersection/plane.c"
	"${CMAKE_CURRENT_LIST_DIR}/intersection/cone.c"
	"${CMAKE_CURRENT_LIST_DIR}/intersection/cylinder.c"
)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
