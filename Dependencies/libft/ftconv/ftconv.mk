FTCONV_DIR	:=	$(LIBFT_DIR)ftconv/
FTCONV_SRC	:=	ft_atoi.c\
				ft_atod.c\
				ft_binary_ulltoa.c\
				ft_hex_atoui.c\
				ft_hex_uitoa.c\
				ft_hex_ulltoa.c\
				ft_itoa.c\
				ft_itoa_cat.c\
				ft_ldtoa.c\
				ft_lltoa.c\
				ft_octal_uitoa.c\
				ft_octal_ulltoa.c\
				ft_uitoa.c\
				ft_ulltoa.c\

FTCONV_OBJ	=	$(addprefix $(LIBFT_OBJ_DIR), $(FTCONV_SRC:.c=.o))
LIBFT_SRC	+=	$(addprefix $(FTCONV_DIR), $(FTCONV_SRC:.c=.o))
LIBFT_OBJ	+=	$(FTCONV_OBJ)

$(FTCONV_OBJ): $(LIBFT_OBJ_DIR)%.o: $(FTCONV_DIR)%.c
	$(CC) $(LIBFT_CFLAGS) $(LIBFT_INCLUDE) $< -o $@
