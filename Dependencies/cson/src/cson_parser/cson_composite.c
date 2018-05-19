/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_object_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson_parser.h"

static t_handler_status	create_composite_value(t_cson_parser *parser,
int state, int value_type)
{
	parser->parent = parser->current;
	parser->current->value.tuple = alst_create(3);
	parser->state = state;
	parser->current->value_type = value_type;
	if (parser->current->value.tuple == NULL)
	{
		cson_log_error(parser, strerror(errno), CSON_MEM_ALLOC_ERROR);
		return (handler_error);
	}
	return (handler_skip);
}

inline t_handler_status	cson_compose_array(t_cson_parser *parser)
{
	return (create_composite_value(parser,
	CSON_PARSER_BEFORE_VALUE_STATE, CSON_ARRAY_VALUE_TYPE));
}

inline t_handler_status	cson_compose_object(t_cson_parser *parser)
{
	return (create_composite_value(parser,
	CSON_PARSER_BEFORE_KEY_STATE, CSON_OBJECT_VALUE_TYPE));
}
