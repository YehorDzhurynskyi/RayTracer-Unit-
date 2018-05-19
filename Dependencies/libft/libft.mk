include $(LIBFT_DIR)ftalst/ftalst.mk
include $(LIBFT_DIR)ftamap/ftamap.mk
include $(LIBFT_DIR)ftchar/ftchar.mk
include $(LIBFT_DIR)ftconv/ftconv.mk
include $(LIBFT_DIR)ftcore/ftcore.mk
include $(LIBFT_DIR)ftfile/ftfile.mk
include $(LIBFT_DIR)ftfloat/ftfloat.mk
include $(LIBFT_DIR)ftio/ftio.mk
include $(LIBFT_DIR)ftlst/ftlst.mk
include $(LIBFT_DIR)ftmath/ftmath.mk
include $(LIBFT_DIR)ftmisc/ftmisc.mk
include $(LIBFT_DIR)ftsort/ftsort.mk
include $(LIBFT_DIR)ftstack/ftstack.mk
include $(LIBFT_DIR)ftstr/ftstr.mk
include $(LIBFT_DIR)fttime/fttime.mk

$(LIBFT): $(LIBFT_OBJ)
	ar rc $@ $^
	ranlib $@
