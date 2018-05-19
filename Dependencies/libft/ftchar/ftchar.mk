FTCHAR_DIR	:=	$(LIBFT_DIR)ftchar/
FTCHAR_SRC	:=	ft_isalnum.c\
				ft_isalpha.c\
				ft_isascii.c\
				ft_isdigit.c\
				ft_isprint.c\
				ft_isws.c\
				ft_ishex.c\
				ft_tolower.c\
				ft_toupper.c\

FTCHAR_OBJ	=	$(addprefix $(LIBFT_OBJ_DIR), $(FTCHAR_SRC:.c=.o))
LIBFT_SRC	+=	$(addprefix $(FTCHAR_DIR), $(FTCHAR_SRC:.c=.o))
LIBFT_OBJ	+=	$(FTCHAR_OBJ)

$(FTCHAR_OBJ): $(LIBFT_OBJ_DIR)%.o: $(FTCHAR_DIR)%.c
	$(CC) $(LIBFT_CFLAGS) $(LIBFT_INCLUDE) $< -o $@
