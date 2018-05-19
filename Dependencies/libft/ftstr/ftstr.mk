FTSTR_DIR	:=	$(LIBFT_DIR)ftstr/
FTSTR_SRC	:=	ft_strcat.c\
				ft_strchr.c\
				ft_strclr.c\
				ft_strcmp.c\
				ft_strcpy.c\
				ft_strdel.c\
				ft_strdup.c\
				ft_strequ.c\
				ft_striter.c\
				ft_striteri.c\
				ft_strjoin.c\
				ft_strlcat.c\
				ft_strlen.c\
				ft_strmap.c\
				ft_strmapi.c\
				ft_strncat.c\
				ft_strnchr.c\
				ft_strchrn.c\
				ft_strncmp.c\
				ft_strncpy.c\
				ft_strnequ.c\
				ft_strnew.c\
				ft_strnstr.c\
				ft_strrchr.c\
				ft_strreplallchr.c\
				ft_strreplallstr.c\
				ft_strsplit.c\
				ft_strstr.c\
				ft_strsub.c\
				ft_strtrim.c\

FTSTR_OBJ	=	$(addprefix $(LIBFT_OBJ_DIR), $(FTSTR_SRC:.c=.o))
LIBFT_SRC	+=	$(addprefix $(FTSTR_DIR), $(FTSTR_SRC:.c=.o))
LIBFT_OBJ	+=	$(FTSTR_OBJ)

$(FTSTR_OBJ): $(LIBFT_OBJ_DIR)%.o: $(FTSTR_DIR)%.c
	$(CC) $(LIBFT_CFLAGS) $(LIBFT_INCLUDE) $< -o $@
