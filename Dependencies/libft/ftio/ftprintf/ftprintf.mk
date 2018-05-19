FTPRINTF_DIR	:=	$(LIBFT_DIR)ftio/ftprintf/
FTPRINTF_SRC	:=	output_color.c\
					conversion.c\
					conversion_handler.c\
					conversion_recognizer.c\
					ereal.c\
					freal.c\
					greal.c\
					hhinteger.c\
					hinteger.c\
					integer.c\
					jinteger.c\
					linteger.c\
					llinteger.c\
					multibyte.c\
					number_manager.c\
					output.c\
					parser.c\
					printf.c\
					ftprintf.c\
					real.c\
					real_manager.c\
					recognizer.c\
					text_manager.c\
					tinteger.c\
					wildcard.c\
					wtext_manager.c\
					zinteger.c\

FTPRINTFOBJ_DIR	=	$(LIBFT_OBJ_DIR)ftprintf/
FTPRINTF_INC	=	-I$(FTPRINTF_DIR)include/

FTPRINTF_OBJ	=	$(addprefix $(FTPRINTFOBJ_DIR), $(FTPRINTF_SRC:.c=.o))
LIBFT_SRC		+=	$(addprefix $(FTPRINTF_DIR), $(FTPRINTF_SRC:.c=.o))
LIBFT_OBJ		+=	$(FTPRINTF_OBJ)

$(FTPRINTF_OBJ): $(FTPRINTFOBJ_DIR)%.o: $(FTPRINTF_DIR)%.c
	$(CC) $(LIBFT_CFLAGS) $(FTPRINTF_INC) $(LIBFT_INCLUDE) $< -o $@
