include $(CSON_DIR)src/src.mk
include $(CSON_DIR)src/cson_parser/cson_parser.mk
include $(CSON_DIR)src/cson_navigator/cson_navigator.mk

$(CSON): $(CSON_OBJ)
	ar rc $@ $^
	ranlib $@
