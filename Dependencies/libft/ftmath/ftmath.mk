FTMATH_DIR	:=	$(LIBFT_DIR)ftmath/
FTMATH_SRC	:=	ft_math_ceil.c\
				ft_math_fabs.c\
				ft_math_fsqrt.c\
				ft_math_pow.c\
				ft_math_round.c\

FTMATH_OBJ	=	$(addprefix $(LIBFT_OBJ_DIR), $(FTMATH_SRC:.c=.o))
LIBFT_SRC	+=	$(addprefix $(FTMATH_DIR), $(FTMATH_SRC:.c=.o))
LIBFT_OBJ	+=	$(FTMATH_OBJ)

$(FTMATH_OBJ): $(LIBFT_OBJ_DIR)%.o: $(FTMATH_DIR)%.c
	$(CC) $(LIBFT_CFLAGS) $(LIBFT_INCLUDE) $< -o $@

include $(LIBFT_DIR)ftmath/vec/vec.mk
include $(LIBFT_DIR)ftmath/mat/mat.mk
include $(LIBFT_DIR)ftmath/complex/complex.mk