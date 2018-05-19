/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_boolean_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson_parser.h"

t_handler_status	cson_boolean_handler(t_cson_parser *parser, char ch)
{
	if (ft_isws(ch))
	{
		if (cson_assign_value(parser) == FALSE)
			return (handler_error);
		return (cson_eov_handler(parser, ch));
	}
	return (handler_record);
}
