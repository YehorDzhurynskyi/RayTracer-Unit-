FTFILE_DIR	:=	$(LIBFT_DIR)ftfile/
FTFILE_SRC	:=	ft_get_basename_part.c\
				ft_get_dir_part.c\
				ft_merge_file_names.c\
				ft_read_file.c\

FTFILE_OBJ	=	$(addprefix $(LIBFT_OBJ_DIR), $(FTFILE_SRC:.c=.o))
LIBFT_SRC	+=	$(addprefix $(FTFILE_DIR), $(FTFILE_SRC:.c=.o))
LIBFT_OBJ	+=	$(FTFILE_OBJ)

$(FTFILE_OBJ): $(LIBFT_OBJ_DIR)%.o: $(FTFILE_DIR)%.c
	$(CC) $(LIBFT_CFLAGS) $(LIBFT_INCLUDE) $< -o $@
