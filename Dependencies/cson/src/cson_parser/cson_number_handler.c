/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_number_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson_parser.h"

static t_bool		check_for_fractional_delimeter(t_cson_parser *parser)
{
	if (ft_strnchr(parser->buffer, '.', parser->buffer_offset) != NULL)
	{
		cson_log_error(parser, "wrong number of \".\" in number value",
		CSON_VALUE_PARSING_ERROR);
		return (FALSE);
	}
	return (TRUE);
}

t_handler_status	cson_number_handler(t_cson_parser *parser, char ch)
{
	if (ft_isws(ch))
	{
		if (cson_assign_value(parser) == FALSE)
			return (handler_error);
		return (cson_eov_handler(parser, ch));
	}
	if (!ft_isdigit(ch) && ch != '.')
	{
		cson_log_parsing_error(parser, "unrecognized symbol in number value",
		ch, CSON_VALUE_PARSING_ERROR);
		return (handler_error);
	}
	if (ch == '.' && check_for_fractional_delimeter(parser) == FALSE)
		return (handler_error);
	return (handler_record);
}
