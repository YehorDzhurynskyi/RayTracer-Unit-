FTAMAP_DIR	:=	$(LIBFT_DIR)ftamap/
FTAMAP_SRC	:=	ft_amap_contains.c\
				ft_amap_create.c\
				ft_amap_init.c\
				ft_amap_clear.c\
				ft_amap_get.c\
				ft_amap_put.c\
				ft_amap_remove.c\

FTAMAP_OBJ	=	$(addprefix $(LIBFT_OBJ_DIR), $(FTAMAP_SRC:.c=.o))
LIBFT_SRC	+=	$(addprefix $(FTAMAP_DIR), $(FTAMAP_SRC:.c=.o))
LIBFT_OBJ	+=	$(FTAMAP_OBJ)

$(FTAMAP_OBJ): $(LIBFT_OBJ_DIR)%.o: $(FTAMAP_DIR)%.c
	$(CC) $(LIBFT_CFLAGS) $(LIBFT_INCLUDE) $< -o $@
