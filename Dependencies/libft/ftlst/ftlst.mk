FTLST_DIR	:=	$(LIBFT_DIR)ftlst/
FTLST_SRC	:=	ft_lstadd.c\
				ft_lstdel.c\
				ft_lstdelone.c\
				ft_lstreduce.c\
				ft_lstiter.c\
				ft_lstmap.c\
				ft_lstnew.c\

FTLST_OBJ	=	$(addprefix $(LIBFT_OBJ_DIR), $(FTLST_SRC:.c=.o))
LIBFT_SRC	+=	$(addprefix $(FTLST_DIR), $(FTLST_SRC:.c=.o))
LIBFT_OBJ	+=	$(FTLST_OBJ)

$(FTLST_OBJ): $(LIBFT_OBJ_DIR)%.o: $(FTLST_DIR)%.c
	$(CC) $(LIBFT_CFLAGS) $(LIBFT_INCLUDE) $< -o $@
