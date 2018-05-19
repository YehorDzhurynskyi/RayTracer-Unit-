VEC_DIR	:=	$(LIBFT_DIR)ftmath/vec/
VEC_SRC	:=	vec_add.c\
			vec_cross.c\
			vec_dot.c\
			vec_length.c\
			vec_normalize.c\
			vec_sub.c\
			vec_scalar.c\
			vec_reflect.c\
			vec_mult.c\
			to_vec3.c\
			vec_print.c\
			vec2rgba.c\
			rgba2vec.c\

VEC_OBJ	=	$(addprefix $(LIBFT_OBJ_DIR), $(VEC_SRC:.c=.o))
LIBFT_SRC	+=	$(addprefix $(VEC_DIR), $(VEC_SRC:.c=.o))
LIBFT_OBJ	+=	$(VEC_OBJ)

$(VEC_OBJ): $(LIBFT_OBJ_DIR)%.o: $(VEC_DIR)%.c
	$(CC) $(LIBFT_CFLAGS) $(LIBFT_INCLUDE) $< -o $@
