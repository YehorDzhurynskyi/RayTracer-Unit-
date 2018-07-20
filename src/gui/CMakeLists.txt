target_sources(${PROJECT_NAME} PUBLIC
	"${CMAKE_CURRENT_LIST_DIR}/gui.c"
	"${CMAKE_CURRENT_LIST_DIR}/gui_style.c"
	"${CMAKE_CURRENT_LIST_DIR}/gui_scene_menu.c"
	"${CMAKE_CURRENT_LIST_DIR}/gui_choose_scene.c"
	"${CMAKE_CURRENT_LIST_DIR}/gui_loading.c"
	"${CMAKE_CURRENT_LIST_DIR}/gui_render.c"
	"${CMAKE_CURRENT_LIST_DIR}/gui_screenshot.c"
	"${CMAKE_CURRENT_LIST_DIR}/gui_choose_device.c"
	"${CMAKE_CURRENT_LIST_DIR}/gui_color_picker.c"

	"${CMAKE_CURRENT_LIST_DIR}/gui_scene_menu.c"
	"${CMAKE_CURRENT_LIST_DIR}/gui_info_log.c"

	"${CMAKE_CURRENT_LIST_DIR}/input/camera_handler.c"
	"${CMAKE_CURRENT_LIST_DIR}/input/pick_shape.c"
	"${CMAKE_CURRENT_LIST_DIR}/input/gui_events.c"

	"${CMAKE_CURRENT_LIST_DIR}/scenetree/gui_scene_tree.c"
	"${CMAKE_CURRENT_LIST_DIR}/scenetree/gui_shape_tree.c"
	"${CMAKE_CURRENT_LIST_DIR}/scenetree/gui_lightsource_tree.c"
	"${CMAKE_CURRENT_LIST_DIR}/scenetree/gui_material_tree.c"

	"${CMAKE_CURRENT_LIST_DIR}/form/gui_object_form.c"
	"${CMAKE_CURRENT_LIST_DIR}/form/gui_shape_form.c"
	"${CMAKE_CURRENT_LIST_DIR}/form/gui_material_form.c"
	"${CMAKE_CURRENT_LIST_DIR}/form/gui_lightsource_form.c"
	"${CMAKE_CURRENT_LIST_DIR}/form/gui_primitive_form.c"
	"${CMAKE_CURRENT_LIST_DIR}/form/gui_sphere_form.c"
	"${CMAKE_CURRENT_LIST_DIR}/form/gui_cylinder_form.c"
	"${CMAKE_CURRENT_LIST_DIR}/form/gui_cone_form.c"
)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}")