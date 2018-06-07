/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_push.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson.h"

void	cson_push_integer(t_cson *cson, int value)
{
	cson_push(cson, cson_integer(value));
}

void	cson_push_real(t_cson *cson, double value)
{
	cson_push(cson, cson_real(value));
}

void	cson_push_boolean(t_cson *cson, t_bool value)
{
	cson_push(cson, cson_boolean(value));
}

void	cson_push_string(t_cson *cson, const char *value)
{
	cson_push(cson, cson_string(value));
}

void	cson_push(t_cson *cson, t_cson *value)
{
	if (cson_is_array(cson) == FALSE)
		return ;
	value->parent = cson;
	alst_add(cson->value.tuple, value);
}
