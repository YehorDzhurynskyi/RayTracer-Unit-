FTTIME_DIR	:=	$(LIBFT_DIR)fttime/
FTTIME_SRC	:=	ft_month.c\
				ft_year.c\

FTTIME_OBJ	=	$(addprefix $(LIBFT_OBJ_DIR), $(FTTIME_SRC:.c=.o))
LIBFT_SRC	+=	$(addprefix $(FTTIME_DIR), $(FTTIME_SRC:.c=.o))
LIBFT_OBJ	+=	$(FTTIME_OBJ)

$(FTTIME_OBJ): $(LIBFT_OBJ_DIR)%.o: $(FTTIME_DIR)%.c
	$(CC) $(LIBFT_CFLAGS) $(LIBFT_INCLUDE) $< -o $@
