FTALST_DIR	:=	$(LIBFT_DIR)ftalst/
FTALST_SRC	:=	ft_alst_add.c\
				ft_alst_clear.c\
				ft_alst_create.c\
				ft_alst_del.c\
				ft_alst_get.c\
				ft_alst_iteri.c\
				ft_alst_remove.c\
				ft_alst_get_index.c\
				ft_alst_to_array.c\

FTALST_OBJ	=	$(addprefix $(LIBFT_OBJ_DIR), $(FTALST_SRC:.c=.o))
LIBFT_SRC	+=	$(addprefix $(FTALST_DIR), $(FTALST_SRC:.c=.o))
LIBFT_OBJ	+=	$(FTALST_OBJ)

$(FTALST_OBJ): $(LIBFT_OBJ_DIR)%.o: $(FTALST_DIR)%.c
	$(CC) $(LIBFT_CFLAGS) $(LIBFT_INCLUDE) $< -o $@
