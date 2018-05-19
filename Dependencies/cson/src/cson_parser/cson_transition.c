/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_transition.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson_parser.h"

static t_state_handler	determine_state_handler(int state)
{
	static t_state_handler	state_handler_pool[] = {
		cson_before_key_handler,
		cson_key_handler,
		cson_after_key_handler,
		cson_before_value_handler,
		cson_string_handler,
		cson_number_handler,
		cson_boolean_handler,
		cson_boolean_handler,
		cson_eov_handler
	};

	return (state_handler_pool[state]);
}

static t_handler_status	handle_bounds(t_cson_parser *parser, char ch)
{
	if (ch == ']')
		parser->array_depth--;
	else if (ch == '[')
		parser->array_depth++;
	else if (ch == '}')
		parser->bounded_object_depth--;
	else if (ch == '{')
		parser->bounded_object_depth++;
	if (ch == ']' || ch == '}')
	{
		if (cson_assign_value(parser) == FALSE)
			return (handler_error);
		parser->parent = parser->parent->parent;
		return (handler_skip);
	}
	return (handler_record);
}

static t_handler_status	status_of_handler(t_cson_parser *parser, char ch)
{
	t_state_handler		state_handler;
	t_handler_status	status;

	status = handler_record;
	if (ch == '#')
		parser->is_comment = TRUE;
	if (ch == '\n')
	{
		parser->current_line++;
		parser->is_comment = FALSE;
	}
	if (parser->is_comment)
		return (handler_skip);
	if (parser->state != CSON_PARSER_KEY_STATE
	&& parser->state != CSON_PARSER_STRING_VALUE_STATE)
		status = handle_bounds(parser, ch);
	if (status != handler_record)
		return (status);
	state_handler = determine_state_handler(parser->state);
	return (state_handler(parser, ch));
}

void					cson_parse_chunk(t_cson_parser *parser,
const char *buffer, size_t size)
{
	int					i;
	t_handler_status	status;

	i = -1;
	while (++i < (int)size)
	{
		status = status_of_handler(parser, buffer[i]);
		if (status == handler_error)
			return ;
		if (status == handler_skip)
			continue ;
		if (cson_ensure_buffer_capacity(parser) == FALSE)
		{
			cson_log_error(parser, strerror(errno), CSON_MEM_ALLOC_ERROR);
			return ;
		}
		parser->buffer[parser->buffer_offset++] = buffer[i];
	}
}
