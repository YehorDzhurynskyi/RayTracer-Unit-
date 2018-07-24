cmake_minimum_required(VERSION 2.8)

project(ft)

add_library(${PROJECT_NAME} STATIC
# ftalst
	${CMAKE_CURRENT_LIST_DIR}/ftalst/ft_alst_add.c
	${CMAKE_CURRENT_LIST_DIR}/ftalst/ft_alst_clear.c
	${CMAKE_CURRENT_LIST_DIR}/ftalst/ft_alst_create.c
	${CMAKE_CURRENT_LIST_DIR}/ftalst/ft_alst_del.c
	${CMAKE_CURRENT_LIST_DIR}/ftalst/ft_alst_get.c
	${CMAKE_CURRENT_LIST_DIR}/ftalst/ft_alst_get_index.c
	${CMAKE_CURRENT_LIST_DIR}/ftalst/ft_alst_iteri.c
	${CMAKE_CURRENT_LIST_DIR}/ftalst/ft_alst_remove.c
	${CMAKE_CURRENT_LIST_DIR}/ftalst/ft_alst_to_array.c

# ftamap
	${CMAKE_CURRENT_LIST_DIR}/ftamap/ft_amap_clear.c
	${CMAKE_CURRENT_LIST_DIR}/ftamap/ft_amap_contains.c
	${CMAKE_CURRENT_LIST_DIR}/ftamap/ft_amap_create.c
	${CMAKE_CURRENT_LIST_DIR}/ftamap/ft_amap_get.c
	${CMAKE_CURRENT_LIST_DIR}/ftamap/ft_amap_init.c
	${CMAKE_CURRENT_LIST_DIR}/ftamap/ft_amap_put.c
	${CMAKE_CURRENT_LIST_DIR}/ftamap/ft_amap_remove.c

# ftchar
	${CMAKE_CURRENT_LIST_DIR}/ftchar/ft_isalnum.c
	${CMAKE_CURRENT_LIST_DIR}/ftchar/ft_isalpha.c
	${CMAKE_CURRENT_LIST_DIR}/ftchar/ft_isascii.c
	${CMAKE_CURRENT_LIST_DIR}/ftchar/ft_isdigit.c
	${CMAKE_CURRENT_LIST_DIR}/ftchar/ft_ishex.c
	${CMAKE_CURRENT_LIST_DIR}/ftchar/ft_isprint.c
	${CMAKE_CURRENT_LIST_DIR}/ftchar/ft_isws.c
	${CMAKE_CURRENT_LIST_DIR}/ftchar/ft_tolower.c
	${CMAKE_CURRENT_LIST_DIR}/ftchar/ft_toupper.c

# ftconv
	${CMAKE_CURRENT_LIST_DIR}/ftconv/ft_atod.c
	${CMAKE_CURRENT_LIST_DIR}/ftconv/ft_atoi.c
	${CMAKE_CURRENT_LIST_DIR}/ftconv/ft_binary_ulltoa.c
	${CMAKE_CURRENT_LIST_DIR}/ftconv/ft_hex_atoui.c
	${CMAKE_CURRENT_LIST_DIR}/ftconv/ft_hex_uitoa.c
	${CMAKE_CURRENT_LIST_DIR}/ftconv/ft_hex_ulltoa.c
	${CMAKE_CURRENT_LIST_DIR}/ftconv/ft_itoa.c
	${CMAKE_CURRENT_LIST_DIR}/ftconv/ft_itoa_cat.c
	${CMAKE_CURRENT_LIST_DIR}/ftconv/ft_ldtoa.c
	${CMAKE_CURRENT_LIST_DIR}/ftconv/ft_lltoa.c
	${CMAKE_CURRENT_LIST_DIR}/ftconv/ft_octal_uitoa.c
	${CMAKE_CURRENT_LIST_DIR}/ftconv/ft_octal_ulltoa.c
	${CMAKE_CURRENT_LIST_DIR}/ftconv/ft_uitoa.c
	${CMAKE_CURRENT_LIST_DIR}/ftconv/ft_ulltoa.c

# ftcore
	${CMAKE_CURRENT_LIST_DIR}/ftcore/ft_bzero.c
	${CMAKE_CURRENT_LIST_DIR}/ftcore/ft_memalloc.c
	${CMAKE_CURRENT_LIST_DIR}/ftcore/ft_memccpy.c
	${CMAKE_CURRENT_LIST_DIR}/ftcore/ft_memchr.c
	${CMAKE_CURRENT_LIST_DIR}/ftcore/ft_memcmp.c
	${CMAKE_CURRENT_LIST_DIR}/ftcore/ft_memcpy.c
	${CMAKE_CURRENT_LIST_DIR}/ftcore/ft_memdel.c
	${CMAKE_CURRENT_LIST_DIR}/ftcore/ft_memmove.c
	${CMAKE_CURRENT_LIST_DIR}/ftcore/ft_memset.c

# ftfile
	${CMAKE_CURRENT_LIST_DIR}/ftfile/ft_get_basename_part.c
	${CMAKE_CURRENT_LIST_DIR}/ftfile/ft_get_dir_part.c
	${CMAKE_CURRENT_LIST_DIR}/ftfile/ft_merge_file_names.c
	${CMAKE_CURRENT_LIST_DIR}/ftfile/ft_read_file.c

# ftfloat
	${CMAKE_CURRENT_LIST_DIR}/ftfloat/ft_float_frac.c
	${CMAKE_CURRENT_LIST_DIR}/ftfloat/ft_float_inf.c
	${CMAKE_CURRENT_LIST_DIR}/ftfloat/ft_float_nan.c
	${CMAKE_CURRENT_LIST_DIR}/ftfloat/ft_float_neg.c

# ftio
	${CMAKE_CURRENT_LIST_DIR}/ftio/ft_putchar.c
	${CMAKE_CURRENT_LIST_DIR}/ftio/ft_putchar_fd.c
	${CMAKE_CURRENT_LIST_DIR}/ftio/ft_putendl.c
	${CMAKE_CURRENT_LIST_DIR}/ftio/ft_putendl_fd.c
	${CMAKE_CURRENT_LIST_DIR}/ftio/ft_putnbr.c
	${CMAKE_CURRENT_LIST_DIR}/ftio/ft_putnbr_fd.c
	${CMAKE_CURRENT_LIST_DIR}/ftio/ft_putstr.c
	${CMAKE_CURRENT_LIST_DIR}/ftio/ft_putstr_fd.c
	${CMAKE_CURRENT_LIST_DIR}/ftio/get_next_line.c

# ftio/ftprintf
	${CMAKE_CURRENT_LIST_DIR}/ftio/ftprintf/conversion.c
	${CMAKE_CURRENT_LIST_DIR}/ftio/ftprintf/conversion_handler.c
	${CMAKE_CURRENT_LIST_DIR}/ftio/ftprintf/conversion_recognizer.c
	${CMAKE_CURRENT_LIST_DIR}/ftio/ftprintf/ereal.c
	${CMAKE_CURRENT_LIST_DIR}/ftio/ftprintf/freal.c
	${CMAKE_CURRENT_LIST_DIR}/ftio/ftprintf/ftprintf.c
	${CMAKE_CURRENT_LIST_DIR}/ftio/ftprintf/greal.c
	${CMAKE_CURRENT_LIST_DIR}/ftio/ftprintf/hhinteger.c
	${CMAKE_CURRENT_LIST_DIR}/ftio/ftprintf/hinteger.c
	${CMAKE_CURRENT_LIST_DIR}/ftio/ftprintf/integer.c
	${CMAKE_CURRENT_LIST_DIR}/ftio/ftprintf/jinteger.c
	${CMAKE_CURRENT_LIST_DIR}/ftio/ftprintf/linteger.c
	${CMAKE_CURRENT_LIST_DIR}/ftio/ftprintf/llinteger.c
	${CMAKE_CURRENT_LIST_DIR}/ftio/ftprintf/multibyte.c
	${CMAKE_CURRENT_LIST_DIR}/ftio/ftprintf/number_manager.c
	${CMAKE_CURRENT_LIST_DIR}/ftio/ftprintf/output.c
	${CMAKE_CURRENT_LIST_DIR}/ftio/ftprintf/output_color.c
	${CMAKE_CURRENT_LIST_DIR}/ftio/ftprintf/parser.c
	${CMAKE_CURRENT_LIST_DIR}/ftio/ftprintf/printf.c
	${CMAKE_CURRENT_LIST_DIR}/ftio/ftprintf/real.c
	${CMAKE_CURRENT_LIST_DIR}/ftio/ftprintf/real_manager.c
	${CMAKE_CURRENT_LIST_DIR}/ftio/ftprintf/recognizer.c
	${CMAKE_CURRENT_LIST_DIR}/ftio/ftprintf/text_manager.c
	${CMAKE_CURRENT_LIST_DIR}/ftio/ftprintf/tinteger.c
	${CMAKE_CURRENT_LIST_DIR}/ftio/ftprintf/wildcard.c
	${CMAKE_CURRENT_LIST_DIR}/ftio/ftprintf/wtext_manager.c
	${CMAKE_CURRENT_LIST_DIR}/ftio/ftprintf/zinteger.c

# ftlst
	${CMAKE_CURRENT_LIST_DIR}/ftlst/ft_lstadd.c
	${CMAKE_CURRENT_LIST_DIR}/ftlst/ft_lstdel.c
	${CMAKE_CURRENT_LIST_DIR}/ftlst/ft_lstdelone.c
	${CMAKE_CURRENT_LIST_DIR}/ftlst/ft_lstiter.c
	${CMAKE_CURRENT_LIST_DIR}/ftlst/ft_lstmap.c
	${CMAKE_CURRENT_LIST_DIR}/ftlst/ft_lstnew.c
	${CMAKE_CURRENT_LIST_DIR}/ftlst/ft_lstreduce.c

# ftmath
	${CMAKE_CURRENT_LIST_DIR}/ftmath/ft_math_ceil.c
	${CMAKE_CURRENT_LIST_DIR}/ftmath/ft_math_fabs.c
	${CMAKE_CURRENT_LIST_DIR}/ftmath/ft_math_fsqrt.c
	${CMAKE_CURRENT_LIST_DIR}/ftmath/ft_math_pow.c
	${CMAKE_CURRENT_LIST_DIR}/ftmath/ft_math_round.c

# ftmath/complex
	${CMAKE_CURRENT_LIST_DIR}/ftmath/complex/complex_add.c
	${CMAKE_CURRENT_LIST_DIR}/ftmath/complex/complex_div.c
	${CMAKE_CURRENT_LIST_DIR}/ftmath/complex/complex_prod.c
	${CMAKE_CURRENT_LIST_DIR}/ftmath/complex/complex_sub.c

# ftmath/mat
	${CMAKE_CURRENT_LIST_DIR}/ftmath/mat/mat3_determinant.c
	${CMAKE_CURRENT_LIST_DIR}/ftmath/mat/mat4_determinant.c
	${CMAKE_CURRENT_LIST_DIR}/ftmath/mat/mat_create.c
	${CMAKE_CURRENT_LIST_DIR}/ftmath/mat/mat_identity.c
	${CMAKE_CURRENT_LIST_DIR}/ftmath/mat/mat_inverse.c
	${CMAKE_CURRENT_LIST_DIR}/ftmath/mat/mat_mat_mult.c
	${CMAKE_CURRENT_LIST_DIR}/ftmath/mat/mat_minor.c
	${CMAKE_CURRENT_LIST_DIR}/ftmath/mat/mat_print.c
	${CMAKE_CURRENT_LIST_DIR}/ftmath/mat/mat_scalar.c
	${CMAKE_CURRENT_LIST_DIR}/ftmath/mat/mat_transpose.c
	${CMAKE_CURRENT_LIST_DIR}/ftmath/mat/mat_vec_mult.c
	${CMAKE_CURRENT_LIST_DIR}/ftmath/mat/vec_mat_mult.c

# ftmath/vec
	${CMAKE_CURRENT_LIST_DIR}/ftmath/vec/rgba2vec.c
	${CMAKE_CURRENT_LIST_DIR}/ftmath/vec/to_vec3.c
	${CMAKE_CURRENT_LIST_DIR}/ftmath/vec/vec2rgba.c
	${CMAKE_CURRENT_LIST_DIR}/ftmath/vec/vec_add.c
	${CMAKE_CURRENT_LIST_DIR}/ftmath/vec/vec_cross.c
	${CMAKE_CURRENT_LIST_DIR}/ftmath/vec/vec_dot.c
	${CMAKE_CURRENT_LIST_DIR}/ftmath/vec/vec_length.c
	${CMAKE_CURRENT_LIST_DIR}/ftmath/vec/vec_mult.c
	${CMAKE_CURRENT_LIST_DIR}/ftmath/vec/vec_normalize.c
	${CMAKE_CURRENT_LIST_DIR}/ftmath/vec/vec_print.c
	${CMAKE_CURRENT_LIST_DIR}/ftmath/vec/vec_reflect.c
	${CMAKE_CURRENT_LIST_DIR}/ftmath/vec/vec_scalar.c
	${CMAKE_CURRENT_LIST_DIR}/ftmath/vec/vec_sub.c

# ftmisc
	${CMAKE_CURRENT_LIST_DIR}/ftmisc/create_rect.c
	${CMAKE_CURRENT_LIST_DIR}/ftmisc/ft_count_num_length.c
	${CMAKE_CURRENT_LIST_DIR}/ftmisc/ft_iswap.c
	${CMAKE_CURRENT_LIST_DIR}/ftmisc/max.c
	${CMAKE_CURRENT_LIST_DIR}/ftmisc/min.c

# ftsort
	${CMAKE_CURRENT_LIST_DIR}/ftsort/ft_insertion_sort.c
	${CMAKE_CURRENT_LIST_DIR}/ftsort/ft_merge_sort.c
	${CMAKE_CURRENT_LIST_DIR}/ftsort/ft_quick_sort.c
	${CMAKE_CURRENT_LIST_DIR}/ftsort/ft_sort.c

# ftstack
	${CMAKE_CURRENT_LIST_DIR}/ftstack/ft_stack_cleanup.c
	${CMAKE_CURRENT_LIST_DIR}/ftstack/ft_stack_create.c
	${CMAKE_CURRENT_LIST_DIR}/ftstack/ft_stack_pop.c
	${CMAKE_CURRENT_LIST_DIR}/ftstack/ft_stack_push.c

# ftstr
	${CMAKE_CURRENT_LIST_DIR}/ftstr/ft_strcat.c
	${CMAKE_CURRENT_LIST_DIR}/ftstr/ft_strchr.c
	${CMAKE_CURRENT_LIST_DIR}/ftstr/ft_str_ends_with.c
	${CMAKE_CURRENT_LIST_DIR}/ftstr/ft_strchrn.c
	${CMAKE_CURRENT_LIST_DIR}/ftstr/ft_strclr.c
	${CMAKE_CURRENT_LIST_DIR}/ftstr/ft_strcmp.c
	${CMAKE_CURRENT_LIST_DIR}/ftstr/ft_strcpy.c
	${CMAKE_CURRENT_LIST_DIR}/ftstr/ft_strdel.c
	${CMAKE_CURRENT_LIST_DIR}/ftstr/ft_strdup.c
	${CMAKE_CURRENT_LIST_DIR}/ftstr/ft_strequ.c
	${CMAKE_CURRENT_LIST_DIR}/ftstr/ft_striter.c
	${CMAKE_CURRENT_LIST_DIR}/ftstr/ft_striteri.c
	${CMAKE_CURRENT_LIST_DIR}/ftstr/ft_strjoin.c
	${CMAKE_CURRENT_LIST_DIR}/ftstr/ft_strlcat.c
	${CMAKE_CURRENT_LIST_DIR}/ftstr/ft_strlen.c
	${CMAKE_CURRENT_LIST_DIR}/ftstr/ft_strmap.c
	${CMAKE_CURRENT_LIST_DIR}/ftstr/ft_strmapi.c
	${CMAKE_CURRENT_LIST_DIR}/ftstr/ft_strncat.c
	${CMAKE_CURRENT_LIST_DIR}/ftstr/ft_strnchr.c
	${CMAKE_CURRENT_LIST_DIR}/ftstr/ft_strncmp.c
	${CMAKE_CURRENT_LIST_DIR}/ftstr/ft_strncpy.c
	${CMAKE_CURRENT_LIST_DIR}/ftstr/ft_strnequ.c
	${CMAKE_CURRENT_LIST_DIR}/ftstr/ft_strnew.c
	${CMAKE_CURRENT_LIST_DIR}/ftstr/ft_strnstr.c
	${CMAKE_CURRENT_LIST_DIR}/ftstr/ft_strrchr.c
	${CMAKE_CURRENT_LIST_DIR}/ftstr/ft_strreplallchr.c
	${CMAKE_CURRENT_LIST_DIR}/ftstr/ft_strreplallstr.c
	${CMAKE_CURRENT_LIST_DIR}/ftstr/ft_strsplit.c
	${CMAKE_CURRENT_LIST_DIR}/ftstr/ft_strstr.c
	${CMAKE_CURRENT_LIST_DIR}/ftstr/ft_strsub.c
	${CMAKE_CURRENT_LIST_DIR}/ftstr/ft_strtrim.c

# fttime
	${CMAKE_CURRENT_LIST_DIR}/fttime/ft_month.c
	${CMAKE_CURRENT_LIST_DIR}/fttime/ft_year.c
)

target_include_directories(${PROJECT_NAME} PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
	${CMAKE_CURRENT_LIST_DIR}/include
	${CMAKE_CURRENT_LIST_DIR}/ftio/ftprintf/include
)