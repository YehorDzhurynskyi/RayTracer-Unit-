target_sources(${PROJECT_NAME} PUBLIC
	"${CMAKE_CURRENT_LIST_DIR}/main.c"
	"${CMAKE_CURRENT_LIST_DIR}/window.c"
	"${CMAKE_CURRENT_LIST_DIR}/renderer.c"

	"${CMAKE_CURRENT_LIST_DIR}/gui/gui.c"
	"${CMAKE_CURRENT_LIST_DIR}/gui/gui_windows.c"
	"${CMAKE_CURRENT_LIST_DIR}/gui/gui_scenes_pop.c"
	"${CMAKE_CURRENT_LIST_DIR}/gui/gui_shapes_win.c"
	"${CMAKE_CURRENT_LIST_DIR}/gui/gui_object_win.c"
	"${CMAKE_CURRENT_LIST_DIR}/gui/gui_functions.c"

	"${CMAKE_CURRENT_LIST_DIR}/opencl/opencl.c"
	"${CMAKE_CURRENT_LIST_DIR}/opencl/opencl_error.c"
	"${CMAKE_CURRENT_LIST_DIR}/opencl/opencl_program.c"
	"${CMAKE_CURRENT_LIST_DIR}/opencl/opencl_adapter.c"

	"${CMAKE_CURRENT_LIST_DIR}/scene/scene.c"
	"${CMAKE_CURRENT_LIST_DIR}/scene/camera.c"

	"${CMAKE_CURRENT_LIST_DIR}/input/camera_handler.c"
	"${CMAKE_CURRENT_LIST_DIR}/input/pick_shape.c"

	"${CMAKE_CURRENT_LIST_DIR}/utilities/logger.c"
	)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}")

include(${CMAKE_CURRENT_LIST_DIR}/scene/repository/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/scene/editor/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/scene/iterator/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/raytracer/CMakeLists.txt)
