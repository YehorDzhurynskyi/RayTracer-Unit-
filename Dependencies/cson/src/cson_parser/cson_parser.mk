CSON_CSON_PARSER_DIR	:=	$(CSON_DIR)src/cson_parser/
CSON_CSON_PARSER_SRC	:=	cson_assignee.c\
							cson_file_parser.c\
							cson_string_parser.c\
							cson_parser.c\
							cson_transition.c\
							cson_parser_buffer.c\
							cson_composite.c\
							cson_key_handler.c\
							cson_key.c\
							cson_boolean_handler.c\
							cson_eov_handler.c\
							cson_number_handler.c\
							cson_string_handler.c\
							cson_value_handler.c\
							cson_parser_logger.c\

CSON_CSON_PARSER_OBJ	=	$(addprefix $(CSON_OBJ_DIR), $(CSON_CSON_PARSER_SRC:.c=.o))
CSON_CSON_PARSER		+=	$(addprefix $(CSON_CSON_PARSER_DIR), $(CSON_CSON_PARSER_SRC))
CSON_OBJ				+=	$(CSON_CSON_PARSER_OBJ)

$(CSON_CSON_PARSER_OBJ): $(CSON_OBJ_DIR)%.o: $(CSON_CSON_PARSER_DIR)%.c
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@
