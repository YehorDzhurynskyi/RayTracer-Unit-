/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_foreach.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson.h"

void	cson_foreach(const t_cson *cson, void (*func)(const t_cson *item))
{
	unsigned	i;
	t_alst		*tuple;

	func(cson);
	if (cson->value_type != CSON_ARRAY_VALUE_TYPE
	&& cson->value_type != CSON_OBJECT_VALUE_TYPE)
		return ;
	tuple = cson->value.tuple;
	i = 0;
	while (i < tuple->size)
		cson_foreach(alst_get(tuple, i++), func);
}
