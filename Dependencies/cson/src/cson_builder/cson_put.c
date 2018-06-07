/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_put.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson.h"

void	cson_put_integer(t_cson *cson, const char *key, int value)
{
	cson_put(cson, key, cson_integer(value));
}

void	cson_put_boolean(t_cson *cson, const char *key, t_bool value)
{
	cson_put(cson, key, cson_boolean(value));
}

void	cson_put_string(t_cson *cson, const char *key, const char *value)
{
	cson_put(cson, key, cson_string(value));
}

void	cson_put_real(t_cson *cson, const char *key, double value)
{
	cson_put(cson, key, cson_real(value));
}

void	cson_put(t_cson *cson, const char *key, t_cson *value)
{
	if (cson_is_object(cson) == FALSE)
		return ;
	value->parent = cson;
	value->key = ft_strdup(key);
	alst_add(cson->value.tuple, value);
}
