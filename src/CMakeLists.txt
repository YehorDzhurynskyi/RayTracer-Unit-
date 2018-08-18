target_sources(${PROJECT_NAME} PUBLIC
	"${CMAKE_CURRENT_LIST_DIR}/main.c"
	"${CMAKE_CURRENT_LIST_DIR}/window.c"
	"${CMAKE_CURRENT_LIST_DIR}/window_msg_box.c"
	"${CMAKE_CURRENT_LIST_DIR}/renderer.c"
	"${CMAKE_CURRENT_LIST_DIR}/renderer_render.c"

	"${CMAKE_CURRENT_LIST_DIR}/opencl/opencl.c"
	"${CMAKE_CURRENT_LIST_DIR}/opencl/opencl_error.c"
	"${CMAKE_CURRENT_LIST_DIR}/opencl/opencl_program.c"
	"${CMAKE_CURRENT_LIST_DIR}/opencl/opencl_adapter.c"

	"${CMAKE_CURRENT_LIST_DIR}/scene/scene.c"
	"${CMAKE_CURRENT_LIST_DIR}/scene/scene_change.c"
	"${CMAKE_CURRENT_LIST_DIR}/scene/camera.c"

	"${CMAKE_CURRENT_LIST_DIR}/texture/create_surface.c"
	"${CMAKE_CURRENT_LIST_DIR}/texture/create_image.c"
	"${CMAKE_CURRENT_LIST_DIR}/texture/texture_map.c"

	"${CMAKE_CURRENT_LIST_DIR}/vfx/vfx_toggle.c"

	"${CMAKE_CURRENT_LIST_DIR}/utilities/logger.c"
)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}")

include(${CMAKE_CURRENT_LIST_DIR}/scene/repo/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/scene/editor/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/scene/iterator/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/raytracer/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/gui/CMakeLists.txt)
