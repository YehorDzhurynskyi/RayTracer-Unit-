cmake_minimum_required(VERSION 2.8)

project(cson)

add_library(${PROJECT_NAME} STATIC
	${CMAKE_CURRENT_LIST_DIR}/src/cson_allocator.c
	${CMAKE_CURRENT_LIST_DIR}/src/cson_print.c

	${CMAKE_CURRENT_LIST_DIR}/src/cson_navigator/cson_at.c
	${CMAKE_CURRENT_LIST_DIR}/src/cson_navigator/cson_depth.c
	${CMAKE_CURRENT_LIST_DIR}/src/cson_navigator/cson_find.c
	${CMAKE_CURRENT_LIST_DIR}/src/cson_navigator/cson_foreach.c
	${CMAKE_CURRENT_LIST_DIR}/src/cson_navigator/cson_get_composite.c
	${CMAKE_CURRENT_LIST_DIR}/src/cson_navigator/cson_get_primitive.c
	${CMAKE_CURRENT_LIST_DIR}/src/cson_navigator/cson_get_default_primitive.c
	${CMAKE_CURRENT_LIST_DIR}/src/cson_navigator/cson_root.c
	${CMAKE_CURRENT_LIST_DIR}/src/cson_navigator/cson_size.c
	${CMAKE_CURRENT_LIST_DIR}/src/cson_navigator/cson_type_composite.c
	${CMAKE_CURRENT_LIST_DIR}/src/cson_navigator/cson_type_primitive.c
	${CMAKE_CURRENT_LIST_DIR}/src/cson_navigator/cson_valueof.c

	${CMAKE_CURRENT_LIST_DIR}/src/cson_parser/cson_assignee.c
	${CMAKE_CURRENT_LIST_DIR}/src/cson_parser/cson_boolean_handler.c
	${CMAKE_CURRENT_LIST_DIR}/src/cson_parser/cson_composite.c
	${CMAKE_CURRENT_LIST_DIR}/src/cson_parser/cson_eov_handler.c
	${CMAKE_CURRENT_LIST_DIR}/src/cson_parser/cson_file_parser.c
	${CMAKE_CURRENT_LIST_DIR}/src/cson_parser/cson_key.c
	${CMAKE_CURRENT_LIST_DIR}/src/cson_parser/cson_key_handler.c
	${CMAKE_CURRENT_LIST_DIR}/src/cson_parser/cson_number_handler.c
	${CMAKE_CURRENT_LIST_DIR}/src/cson_parser/cson_parser.c
	${CMAKE_CURRENT_LIST_DIR}/src/cson_parser/cson_parser_buffer.c
	${CMAKE_CURRENT_LIST_DIR}/src/cson_parser/cson_string_handler.c
	${CMAKE_CURRENT_LIST_DIR}/src/cson_parser/cson_string_parser.c
	${CMAKE_CURRENT_LIST_DIR}/src/cson_parser/cson_transition.c
	${CMAKE_CURRENT_LIST_DIR}/src/cson_parser/cson_value_handler.c
	${CMAKE_CURRENT_LIST_DIR}/src/cson_parser/cson_parser_logger.c
	
	${CMAKE_CURRENT_LIST_DIR}/src/cson_producer/cson_composite_producer.c
	${CMAKE_CURRENT_LIST_DIR}/src/cson_producer/cson_file_producer.c
	${CMAKE_CURRENT_LIST_DIR}/src/cson_producer/cson_node_producer.c
	${CMAKE_CURRENT_LIST_DIR}/src/cson_producer/cson_primitive_producer.c
	${CMAKE_CURRENT_LIST_DIR}/src/cson_producer/cson_producer.c
	${CMAKE_CURRENT_LIST_DIR}/src/cson_producer/cson_producer_logger.c
	${CMAKE_CURRENT_LIST_DIR}/src/cson_producer/cson_str_producer.c

	${CMAKE_CURRENT_LIST_DIR}/src/cson_builder/cson_builder_primitive.c
	${CMAKE_CURRENT_LIST_DIR}/src/cson_builder/cson_builder_composite.c
	${CMAKE_CURRENT_LIST_DIR}/src/cson_builder/cson_push.c
	${CMAKE_CURRENT_LIST_DIR}/src/cson_builder/cson_put.c
)

target_include_directories(${PROJECT_NAME} PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)
