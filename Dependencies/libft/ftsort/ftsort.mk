FTSORT_DIR	:=	$(LIBFT_DIR)ftsort/
FTSORT_SRC	:=	ft_insertion_sort.c\
				ft_merge_sort.c\
				ft_quick_sort.c\
				ft_sort.c\

FTSORT_OBJ	=	$(addprefix $(LIBFT_OBJ_DIR), $(FTSORT_SRC:.c=.o))
LIBFT_SRC	+=	$(addprefix $(FTSORT_DIR), $(FTSORT_SRC:.c=.o))
LIBFT_OBJ	+=	$(FTSORT_OBJ)

$(FTSORT_OBJ): $(LIBFT_OBJ_DIR)%.o: $(FTSORT_DIR)%.c
	$(CC) $(LIBFT_CFLAGS) $(LIBFT_INCLUDE) $< -o $@
