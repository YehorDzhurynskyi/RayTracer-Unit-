target_sources(${PROJECT_NAME} PUBLIC
	"${CMAKE_CURRENT_LIST_DIR}/main.c"
	"${CMAKE_CURRENT_LIST_DIR}/error.c"
	"${CMAKE_CURRENT_LIST_DIR}/window.c"
	"${CMAKE_CURRENT_LIST_DIR}/renderer.c"
	
	"${CMAKE_CURRENT_LIST_DIR}/gui.c"
	
	"${CMAKE_CURRENT_LIST_DIR}/opencl/opencl.c"
	"${CMAKE_CURRENT_LIST_DIR}/opencl/opencl_program.c"

	"${CMAKE_CURRENT_LIST_DIR}/scene/scene.c"
	"${CMAKE_CURRENT_LIST_DIR}/scene/camera.c"
)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}")

include(${CMAKE_CURRENT_LIST_DIR}/scene/repository/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/scene/editor/CMakeLists.txt)
