CSON_SRC_DIR	:=	$(CSON_DIR)src/
CSON_SRC_SRC	:=	cson_allocator.c\
					cson_print.c\
					cson_logger.c\

CSON_SRC_OBJ	=	$(addprefix $(CSON_OBJ_DIR), $(CSON_SRC_SRC:.c=.o))
CSON_SRC		+=	$(addprefix $(CSON_SRC_DIR), $(CSON_SRC_SRC))
CSON_OBJ		+=	$(CSON_SRC_OBJ)

$(CSON_SRC_OBJ): $(CSON_OBJ_DIR)%.o: $(CSON_SRC_DIR)%.c
	$(CC) $(CSON_CFLAGS) $(CSON_INCLUDE) $< -o $@
