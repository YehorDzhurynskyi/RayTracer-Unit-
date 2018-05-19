COMPLEX_DIR	:=	$(LIBFT_DIR)ftmath/complex/
COMPLEX_SRC	:=	complex_add.c\
				complex_sub.c\
				complex_prod.c\
				complex_div.c\

COMPLEX_OBJ	=	$(addprefix $(LIBFT_OBJ_DIR), $(COMPLEX_SRC:.c=.o))
LIBFT_SRC	+=	$(addprefix $(COMPLEX_DIR), $(COMPLEX_SRC:.c=.o))
LIBFT_OBJ	+=	$(COMPLEX_OBJ)

$(COMPLEX_OBJ): $(LIBFT_OBJ_DIR)%.o: $(COMPLEX_DIR)%.c
	$(CC) $(LIBFT_CFLAGS) $(LIBFT_INCLUDE) $< -o $@
