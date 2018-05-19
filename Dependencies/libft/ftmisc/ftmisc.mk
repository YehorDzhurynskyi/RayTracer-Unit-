FTMISC_DIR	:=	$(LIBFT_DIR)ftmisc/
FTMISC_SRC	:=	create_rect.c\
				ft_count_num_length.c\
				ft_iswap.c\
				max.c\
				min.c\

FTMISC_OBJ	=	$(addprefix $(LIBFT_OBJ_DIR), $(FTMISC_SRC:.c=.o))
LIBFT_SRC	+=	$(addprefix $(FTMISC_DIR), $(FTMISC_SRC:.c=.o))
LIBFT_OBJ	+=	$(FTMISC_OBJ)

$(FTMISC_OBJ): $(LIBFT_OBJ_DIR)%.o: $(FTMISC_DIR)%.c
	$(CC) $(LIBFT_CFLAGS) $(LIBFT_INCLUDE) $< -o $@
