/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_string_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson_parser.h"
#include <stdlib.h>

t_cson	*cson_parse_str(const char *str, size_t size, int *err)
{
	t_cson_parser	parser;

	if (cson_parser_init(&parser, err) == FALSE)
		return (NULL);
	cson_parse_chunk(&parser, str, size);
	return (cson_parser_done(&parser));
}
