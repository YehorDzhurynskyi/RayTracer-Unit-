CSON_CSON_PRODUCER_DIR	:=	$(CSON_DIR)src/cson_producer/
CSON_CSON_PRODUCER_SRC	:=	cson_file_producer.c\
							cson_str_producer.c\
							cson_composite_producer.c\
							cson_primitive_producer.c\
							cson_producer.c\
							cson_node_producer.c\
							cson_producer_logger.c\

CSON_CSON_PRODUCER_OBJ	=	$(addprefix $(CSON_OBJ_DIR), $(CSON_CSON_PRODUCER_SRC:.c=.o))
CSON_CSON_PRODUCER		+=	$(addprefix $(CSON_CSON_PRODUCER_DIR), $(CSON_CSON_PRODUCER_SRC))
CSON_OBJ				+=	$(CSON_CSON_PRODUCER_OBJ)

$(CSON_CSON_PRODUCER_OBJ): $(CSON_OBJ_DIR)%.o: $(CSON_CSON_PRODUCER_DIR)%.c
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@
