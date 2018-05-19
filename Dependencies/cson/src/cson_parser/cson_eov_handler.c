/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_eov_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson_parser.h"

inline static t_bool	is_inside_array(const t_cson_parser *parser)
{
	return (parser->array_depth != 0
	&& parser->parent->value_type == CSON_ARRAY_VALUE_TYPE);
}

t_handler_status		cson_eov_handler(t_cson_parser *parser, char ch)
{
	if (is_inside_array(parser))
	{
		parser->state = CSON_PARSER_BEFORE_VALUE_STATE;
		return (cson_before_value_handler(parser, ch));
	}
	if (ft_isws(ch) == FALSE)
	{
		cson_log_parsing_error(parser, "unrecognized symbol after the value",
		ch, CSON_VALUE_PARSING_ERROR);
		return (handler_error);
	}
	if (ch == '\n')
		parser->state = CSON_PARSER_BEFORE_KEY_STATE;
	return (handler_skip);
}
