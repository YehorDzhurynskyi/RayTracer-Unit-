/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson_parser.h"

static t_bool	cson_assign_string(t_cson_parser *parser)
{
	parser->current->value.string = ft_strsub(parser->buffer + 1,
	0, parser->buffer_offset - 1);
	if (parser->current->value.string == NULL)
		cson_log_error(parser, strerror(errno), CSON_MEM_ALLOC_ERROR);
	parser->current->value_type = CSON_STRING_VALUE_TYPE;
	return (parser->current->value.string != NULL);
}

static t_bool	cson_assign_number(t_cson_parser *parser)
{
	t_bool	is_integer;

	if (parser->buffer_offset == 1
	&& (parser->buffer[0] == '+' || parser->buffer[0] == '-'))
	{
		cson_log_error(parser, "number value can't consist of sign only",
		CSON_VALUE_PARSING_ERROR);
		return (FALSE);
	}
	parser->buffer[parser->buffer_offset] = '\0';
	is_integer = ft_strchr(parser->buffer, '.') == NULL;
	parser->current->value_type = is_integer
	? CSON_INTEGER_VALUE_TYPE : CSON_REAL_VALUE_TYPE;
	if (is_integer)
		parser->current->value.integer = ft_atoi(parser->buffer);
	else
		parser->current->value.real = ft_atod(parser->buffer);
	return (TRUE);
}

static t_bool	cson_assign_boolean(t_cson_parser *parser, int value)
{
	if (value == TRUE && (parser->buffer_offset < 4
	|| !ft_strnequ("true", parser->buffer, parser->buffer_offset)))
	{
		cson_log_error(parser, "invalid value (did you mean \"true\"?)",
		CSON_VALUE_PARSING_ERROR);
		return (FALSE);
	}
	else if (value == FALSE && (parser->buffer_offset < 5
	|| !ft_strnequ("false", parser->buffer, parser->buffer_offset)))
	{
		cson_log_error(parser, "invalid value (did you mean \"false\"?)",
		CSON_VALUE_PARSING_ERROR);
		return (FALSE);
	}
	parser->current->value.boolean = value;
	parser->current->value_type = CSON_BOOLEAN_VALUE_TYPE;
	return (TRUE);
}

t_bool			cson_assign_value(t_cson_parser *parser)
{
	t_bool	res;

	res = TRUE;
	if (parser->state == CSON_PARSER_NUMBER_VALUE_STATE)
		res = cson_assign_number(parser);
	else if (parser->state == CSON_PARSER_STRING_VALUE_STATE)
		res = cson_assign_string(parser);
	else if (parser->state == CSON_PARSER_TRUE_VALUE_STATE)
		res = cson_assign_boolean(parser, TRUE);
	else if (parser->state == CSON_PARSER_FALSE_VALUE_STATE)
		res = cson_assign_boolean(parser, FALSE);
	parser->buffer_offset = 0;
	parser->state = CSON_PARSER_EOV_STATE;
	return (res);
}
