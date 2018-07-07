target_sources(${PROJECT_NAME} PUBLIC
	"${CMAKE_CURRENT_LIST_DIR}/gui.c"
	"${CMAKE_CURRENT_LIST_DIR}/gui_mainmnu_win.c"
	"${CMAKE_CURRENT_LIST_DIR}/gui_scenes_pop.c"
	"${CMAKE_CURRENT_LIST_DIR}/gui_shapes_win.c"
	"${CMAKE_CURRENT_LIST_DIR}/gui_object_win.c"
	"${CMAKE_CURRENT_LIST_DIR}/gui_functions.c"
)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}")