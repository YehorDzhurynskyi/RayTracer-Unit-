FTIO_DIR	:=	$(LIBFT_DIR)ftio/
FTIO_SRC	:=	ft_putchar.c\
				ft_putchar_fd.c\
				ft_putstr.c\
				ft_putstr_fd.c\
				ft_putendl.c\
				ft_putendl_fd.c\
				ft_putnbr.c\
				ft_putnbr_fd.c\
				get_next_line.c\

FTIO_OBJ	=	$(addprefix $(LIBFT_OBJ_DIR), $(FTIO_SRC:.c=.o))
LIBFT_SRC	+=	$(addprefix $(FTIO_DIR), $(FTIO_SRC:.c=.o))
LIBFT_OBJ	+=	$(FTIO_OBJ)

$(FTIO_OBJ): $(LIBFT_OBJ_DIR)%.o: $(FTIO_DIR)%.c
	$(CC) $(LIBFT_CFLAGS) $(LIBFT_INCLUDE) $< -o $@

include $(LIBFT_DIR)ftio/ftprintf/ftprintf.mk