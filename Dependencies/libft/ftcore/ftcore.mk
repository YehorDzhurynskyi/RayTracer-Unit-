FTCORE_DIR	:=	$(LIBFT_DIR)ftcore/
FTCORE_SRC	:=	ft_bzero.c\
				ft_memalloc.c\
				ft_memccpy.c\
				ft_memchr.c\
				ft_memcmp.c\
				ft_memcpy.c\
				ft_memdel.c\
				ft_memmove.c\
				ft_memset.c\

FTCORE_OBJ	=	$(addprefix $(LIBFT_OBJ_DIR), $(FTCORE_SRC:.c=.o))
LIBFT_SRC	+=	$(addprefix $(FTCORE_DIR), $(FTCORE_SRC:.c=.o))
LIBFT_OBJ	+=	$(FTCORE_OBJ)

$(FTCORE_OBJ): $(LIBFT_OBJ_DIR)%.o: $(FTCORE_DIR)%.c
	$(CC) $(LIBFT_CFLAGS) $(LIBFT_INCLUDE) $< -o $@
