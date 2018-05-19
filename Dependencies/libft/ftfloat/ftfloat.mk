FTFLOAT_DIR	:=	$(LIBFT_DIR)ftfloat/
FTFLOAT_SRC	:=	ft_float_frac.c\
				ft_float_inf.c\
				ft_float_nan.c\
				ft_float_neg.c\

FTFLOAT_OBJ	=	$(addprefix $(LIBFT_OBJ_DIR), $(FTFLOAT_SRC:.c=.o))
LIBFT_SRC	+=	$(addprefix $(FTFLOAT_DIR), $(FTFLOAT_SRC:.c=.o))
LIBFT_OBJ	+=	$(FTFLOAT_OBJ)

$(FTFLOAT_OBJ): $(LIBFT_OBJ_DIR)%.o: $(FTFLOAT_DIR)%.c
	$(CC) $(LIBFT_CFLAGS) $(LIBFT_INCLUDE) $< -o $@
