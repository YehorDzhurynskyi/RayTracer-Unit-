cmake_minimum_required(VERSION 2.8)

project(nuklear)

add_library(${PROJECT_NAME} STATIC
	${CMAKE_CURRENT_LIST_DIR}/src/nuklear_buffer.c
	${CMAKE_CURRENT_LIST_DIR}/src/nuklear_button.c
	${CMAKE_CURRENT_LIST_DIR}/src/nuklear_chart.c
	${CMAKE_CURRENT_LIST_DIR}/src/nuklear_color.c
	${CMAKE_CURRENT_LIST_DIR}/src/nuklear_color_picker.c
	${CMAKE_CURRENT_LIST_DIR}/src/nuklear_combo.c
	${CMAKE_CURRENT_LIST_DIR}/src/nuklear_context.c
	${CMAKE_CURRENT_LIST_DIR}/src/nuklear_contextual.c
	${CMAKE_CURRENT_LIST_DIR}/src/nuklear_draw.c
	${CMAKE_CURRENT_LIST_DIR}/src/nuklear_edit.c
	${CMAKE_CURRENT_LIST_DIR}/src/nuklear_font.c
	${CMAKE_CURRENT_LIST_DIR}/src/nuklear_group.c
	${CMAKE_CURRENT_LIST_DIR}/src/nuklear_image.c
	${CMAKE_CURRENT_LIST_DIR}/src/nuklear_input.c
	${CMAKE_CURRENT_LIST_DIR}/src/nuklear_layout.c
	${CMAKE_CURRENT_LIST_DIR}/src/nuklear_list_view.c
	${CMAKE_CURRENT_LIST_DIR}/src/nuklear_math.c
	${CMAKE_CURRENT_LIST_DIR}/src/nuklear_menu.c
	${CMAKE_CURRENT_LIST_DIR}/src/nuklear_page_element.c
	${CMAKE_CURRENT_LIST_DIR}/src/nuklear_panel.c
	${CMAKE_CURRENT_LIST_DIR}/src/nuklear_pool.c
	${CMAKE_CURRENT_LIST_DIR}/src/nuklear_popup.c
	${CMAKE_CURRENT_LIST_DIR}/src/nuklear_progress.c
	${CMAKE_CURRENT_LIST_DIR}/src/nuklear_property.c
	${CMAKE_CURRENT_LIST_DIR}/src/nuklear_scrollbar.c
	${CMAKE_CURRENT_LIST_DIR}/src/nuklear_selectable.c
	${CMAKE_CURRENT_LIST_DIR}/src/nuklear_slider.c
	${CMAKE_CURRENT_LIST_DIR}/src/nuklear_string.c
	${CMAKE_CURRENT_LIST_DIR}/src/nuklear_style.c
	${CMAKE_CURRENT_LIST_DIR}/src/nuklear_table.c
	${CMAKE_CURRENT_LIST_DIR}/src/nuklear_text.c
	${CMAKE_CURRENT_LIST_DIR}/src/nuklear_text_editor.c
	${CMAKE_CURRENT_LIST_DIR}/src/nuklear_toggle.c
	${CMAKE_CURRENT_LIST_DIR}/src/nuklear_tooltip.c
	${CMAKE_CURRENT_LIST_DIR}/src/nuklear_tree.c
	${CMAKE_CURRENT_LIST_DIR}/src/nuklear_utf8.c
	${CMAKE_CURRENT_LIST_DIR}/src/nuklear_util.c
	${CMAKE_CURRENT_LIST_DIR}/src/nuklear_vertex.c
	${CMAKE_CURRENT_LIST_DIR}/src/nuklear_widget.c
	${CMAKE_CURRENT_LIST_DIR}/src/nuklear_window.c
)

target_include_directories(${PROJECT_NAME} PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)
