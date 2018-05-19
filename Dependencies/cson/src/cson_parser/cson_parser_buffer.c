/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_parser_buffer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson_parser.h"
#include <stdlib.h>

t_bool	cson_ensure_buffer_capacity(t_cson_parser *parser)
{
	char	*buffer;

	if (parser->buffer_offset == (int)parser->buffer_size - 1)
	{
		buffer = malloc(sizeof(char) * (parser->buffer_size * 2));
		if (buffer == NULL)
			return (FALSE);
		ft_memcpy(buffer, parser->buffer, parser->buffer_size);
		free(parser->buffer);
		parser->buffer_size = parser->buffer_size * 2;
		parser->buffer = buffer;
	}
	return (TRUE);
}

t_bool	cson_flush_buffer(t_cson_parser *parser)
{
	if (parser->state == CSON_PARSER_STRING_VALUE_STATE)
	{
		cson_log_error(parser, "the value of the string"
		" should have a closing quote", CSON_VALUE_PARSING_ERROR);
		return (FALSE);
	}
	return (cson_assign_value(parser));
}
