MAT_DIR	:=	$(LIBFT_DIR)ftmath/mat/
MAT_SRC	:=	mat_identity.c\
			mat_mat_mult.c\
			mat_vec_mult.c\
			vec_mat_mult.c\
			mat_create.c\
			mat_print.c\
			mat3_determinant.c\
			mat4_determinant.c\
			mat_scalar.c\
			mat_inverse.c\
			mat_transpose.c\
			mat_minor.c\

MAT_OBJ	=	$(addprefix $(LIBFT_OBJ_DIR), $(MAT_SRC:.c=.o))
LIBFT_SRC	+=	$(addprefix $(MAT_DIR), $(MAT_SRC:.c=.o))
LIBFT_OBJ	+=	$(MAT_OBJ)

$(MAT_OBJ): $(LIBFT_OBJ_DIR)%.o: $(MAT_DIR)%.c
	$(CC) $(LIBFT_CFLAGS) $(LIBFT_INCLUDE) $< -o $@
