target_sources(${PROJECT_NAME} PUBLIC
	"${CMAKE_CURRENT_LIST_DIR}/intersection/intersection.c"
	"${CMAKE_CURRENT_LIST_DIR}/intersection/intersection_sphere.c"
	"${CMAKE_CURRENT_LIST_DIR}/intersection/intersection_plane.c"
	"${CMAKE_CURRENT_LIST_DIR}/intersection/intersection_cone.c"
	"${CMAKE_CURRENT_LIST_DIR}/intersection/intersection_cylinder.c"
	"${CMAKE_CURRENT_LIST_DIR}/intersection/limit.c"
)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
