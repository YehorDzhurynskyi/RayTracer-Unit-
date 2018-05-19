FTSTACK_DIR	:=	$(LIBFT_DIR)ftstack/
FTSTACK_SRC	:=	ft_stack_cleanup.c\
				ft_stack_create.c\
				ft_stack_pop.c\
				ft_stack_push.c\

FTSTACK_OBJ	=	$(addprefix $(LIBFT_OBJ_DIR), $(FTSTACK_SRC:.c=.o))
LIBFT_SRC	+=	$(addprefix $(FTSTACK_DIR), $(FTSTACK_SRC:.c=.o))
LIBFT_OBJ	+=	$(FTSTACK_OBJ)

$(FTSTACK_OBJ): $(LIBFT_OBJ_DIR)%.o: $(FTSTACK_DIR)%.c
	$(CC) $(LIBFT_CFLAGS) $(LIBFT_INCLUDE) $< -o $@
