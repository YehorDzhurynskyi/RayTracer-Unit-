/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson_parser.h"
#include <stdlib.h>

#define ARRAY_BRACKETS_ERROR_MSG	"wrong number of '[]' (array brackets)"
#define OBJECT_BRACKETS_ERROR_MSG	"wrong number of '{}' (object brackets)"

t_bool	cson_parser_init(t_cson_parser *parser, int *err)
{
	parser->root = cson_alloc(NULL);
	parser->root->value.tuple = alst_create(3);
	parser->root->value_type = CSON_OBJECT_VALUE_TYPE;
	parser->current = parser->root;
	parser->parent = parser->root;
	parser->state = CSON_PARSER_BEFORE_KEY_STATE;
	parser->buffer_size = CSON_PARSER_BSIZE;
	parser->buffer = (char*)malloc(sizeof(char) * parser->buffer_size);
	parser->buffer_offset = 0;
	parser->current_line = 1;
	parser->array_depth = 0;
	parser->bounded_object_depth = 0;
	parser->err = err;
	*parser->err = 0;
	parser->is_comment = FALSE;
	if (parser->root == NULL || parser->root->value.tuple == NULL
	|| parser->buffer == NULL)
	{
		cson_log_error(parser, strerror(errno), CSON_MEM_ALLOC_ERROR);
		cson_parser_fail(parser);
		return (FALSE);
	}
	return (TRUE);
}

void	cson_parser_free(t_cson_parser *parser)
{
	if (parser->root && parser->root->value.tuple->size == 0)
	{
		cson_log_error(parser, "input data is empty",
		CSON_EMPTY_DATA_PARSING_ERROR);
		cson_parser_fail(parser);
	}
	if (parser->array_depth != 0 || parser->bounded_object_depth != 0)
	{
		cson_log_error(parser, parser->array_depth != 0
		? ARRAY_BRACKETS_ERROR_MSG : OBJECT_BRACKETS_ERROR_MSG,
		CSON_BRACKETS_PARSING_ERROR);
		cson_parser_fail(parser);
	}
	free(parser->buffer);
}

void	cson_parser_fail(t_cson_parser *parser)
{
	cson_free(parser->root);
	free(parser->buffer);
	parser->buffer = NULL;
	parser->root = NULL;
}

t_cson	*cson_parser_done(t_cson_parser *parser)
{
	if (*parser->err != 0 || cson_flush_buffer(parser) == FALSE)
		cson_parser_fail(parser);
	cson_parser_free(parser);
	return (parser->root);
}
