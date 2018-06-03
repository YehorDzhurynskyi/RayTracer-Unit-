CSON_CSON_NAVIGATOR_DIR	:=	$(CSON_DIR)src/cson_navigator/
CSON_CSON_NAVIGATOR_SRC	:=	cson_at.c\
							cson_depth.c\
							cson_find.c\
							cson_foreach.c\
							cson_get_composite.c\
							cson_get_primitive.c\
							cson_root.c\
							cson_size.c\
							cson_type_composite.c\
							cson_type_primitive.c\
							cson_valueof.c\

CSON_CSON_NAVIGATOR_OBJ	=	$(addprefix $(CSON_OBJ_DIR), $(CSON_CSON_NAVIGATOR_SRC:.c=.o))
CSON_CSON_NAVIGATOR		+=	$(addprefix $(CSON_CSON_NAVIGATOR_DIR), $(CSON_CSON_NAVIGATOR_SRC))
CSON_OBJ				+=	$(CSON_CSON_NAVIGATOR_OBJ)

$(CSON_CSON_NAVIGATOR_OBJ): $(CSON_OBJ_DIR)%.o: $(CSON_CSON_NAVIGATOR_DIR)%.c
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@
