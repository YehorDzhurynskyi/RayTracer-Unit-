/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_value_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson_parser.h"

inline static t_bool	is_anonymous_value(const t_cson_parser *parser)
{
	return (parser->buffer_offset == 0);
}

t_bool					cson_create_node(t_cson_parser *parser)
{
	parser->current = cson_alloc(parser->parent);
	if (parser->current == NULL)
	{
		cson_log_error(parser, strerror(errno), CSON_MEM_ALLOC_ERROR);
		return (FALSE);
	}
	alst_add(parser->parent->value.tuple, parser->current);
	if (is_anonymous_value(parser))
		parser->current->key = NULL;
	else
	{
		parser->current->key = ft_strsub(parser->buffer,
		0, parser->buffer_offset);
		if (parser->current->key == NULL)
		{
			cson_log_error(parser, strerror(errno), CSON_MEM_ALLOC_ERROR);
			return (FALSE);
		}
	}
	parser->buffer_offset = 0;
	return (TRUE);
}

t_handler_status		cson_before_value_handler(t_cson_parser *parser,
char ch)
{
	if (ft_isws(ch))
		return (handler_skip);
	else if (ch == '[' || ch == '{')
	{
		if (cson_create_node(parser) == FALSE)
			return (handler_error);
		return (ch == '[' ? cson_compose_array(parser)
		: cson_compose_object(parser));
	}
	else if (ch == 't')
		parser->state = CSON_PARSER_TRUE_VALUE_STATE;
	else if (ch == 'f')
		parser->state = CSON_PARSER_FALSE_VALUE_STATE;
	else if (ch == '\'' || ch == '"')
		parser->state = CSON_PARSER_STRING_VALUE_STATE;
	else if (ft_isdigit(ch) || ch == '+' || ch == '-')
		parser->state = CSON_PARSER_NUMBER_VALUE_STATE;
	else
	{
		cson_log_parsing_error(parser, "unrecognized symbol before a value",
		ch, CSON_KEY_PARSING_ERROR);
		return (handler_error);
	}
	return (cson_create_node(parser) ? handler_record : handler_error);
}
