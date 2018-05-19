/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_key_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson_parser.h"

inline static t_bool	has_unbounded_parent(const t_cson_parser *parser)
{
	return (parser->bounded_object_depth == 0);
}

t_handler_status		cson_after_key_handler(t_cson_parser *parser, char ch)
{
	if (ch == '\n')
	{
		if (cson_create_node(parser) == FALSE)
			return (handler_error);
		return (cson_compose_object(parser));
	}
	return (cson_before_value_handler(parser, ch));
}

t_handler_status		cson_key_handler(t_cson_parser *parser, char ch)
{
	if (cson_is_quoted_key(parser))
		return (cson_process_quoted_key(parser, ch));
	if (ch == ':')
	{
		if (parser->buffer_offset == 0)
		{
			cson_log_parsing_error(parser, "cson <key> can't be"
			" an empty string", ch, CSON_KEY_PARSING_ERROR);
			return (handler_error);
		}
		parser->state = has_unbounded_parent(parser)
		? CSON_PARSER_AFTER_KEY_STATE : CSON_PARSER_BEFORE_VALUE_STATE;
		return (handler_skip);
	}
	if (!cson_is_key_symbol(ch))
	{
		cson_log_parsing_error(parser, "cson <key> should contain"
		" only alphanumeric characters and '_'", ch, CSON_KEY_PARSING_ERROR);
		return (handler_error);
	}
	return (handler_record);
}

static t_bool			update_parent_node(t_cson_parser *parser)
{
	int	depth;
	int	i;

	depth = cson_depth(parser->parent);
	if (parser->buffer_offset - depth > 0)
	{
		cson_log_error(parser, "bad identation before key",
		CSON_KEY_PARSING_ERROR);
		return (FALSE);
	}
	i = 0;
	while (i++ < depth - parser->buffer_offset)
		parser->parent = parser->parent->parent;
	return (TRUE);
}

t_handler_status		cson_before_key_handler(t_cson_parser *parser, char ch)
{
	if (cson_is_key_symbol(ch))
	{
		if (has_unbounded_parent(parser) && update_parent_node(parser) == FALSE)
			return (handler_error);
		parser->state = CSON_PARSER_KEY_STATE;
		parser->buffer_offset = 0;
		return (handler_record);
	}
	else if (ft_isws(ch) && ch != '\t')
	{
		parser->buffer_offset = 0;
		return (handler_skip);
	}
	else if (ch != '\t')
	{
		cson_log_parsing_error(parser, "bad symbol before key",
		ch, CSON_KEY_PARSING_ERROR);
		return (handler_error);
	}
	return (handler_record);
}
