CSON_CSON_BUILDER_DIR	:=	$(CSON_DIR)src/cson_builder/
CSON_CSON_BUILDER_SRC	:=	cson_builder_composite.c\
							cson_builder_primitive.c\
							cson_push.c\
							cson_put.c\

CSON_CSON_BUILDER_OBJ	=	$(addprefix $(CSON_OBJ_DIR), $(CSON_CSON_BUILDER_SRC:.c=.o))
CSON_CSON_BUILDER		+=	$(addprefix $(CSON_CSON_BUILDER_DIR), $(CSON_CSON_BUILDER_SRC))
CSON_OBJ				+=	$(CSON_CSON_BUILDER_OBJ)

$(CSON_CSON_BUILDER_OBJ): $(CSON_OBJ_DIR)%.o: $(CSON_CSON_BUILDER_DIR)%.c
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@
