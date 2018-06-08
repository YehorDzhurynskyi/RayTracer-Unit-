/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_allocator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson.h"
#include <stdlib.h>

t_cson	*cson_alloc(t_cson *parent)
{
	t_cson	*cson;

	cson = (t_cson*)malloc(sizeof(t_cson));
	if (!cson)
		return (NULL);
	cson->key = NULL;
	cson->value_type = CSON_UNDEFINED_VALUE_TYPE;
	cson->parent = parent;
	return (cson);
}

void	cson_eliminate(t_cson *cson)
{
	unsigned	i;
	t_alst		*tuple;

	if (cson == NULL)
		return ;
	if (cson->value_type == CSON_OBJECT_VALUE_TYPE
	|| cson->value_type == CSON_ARRAY_VALUE_TYPE)
	{
		tuple = cson->value.tuple;
		i = 0;
		while (i < tuple->size)
			cson_eliminate(alst_get(tuple, i++));
		alst_del(&tuple);
	}
	else if (cson->value_type == CSON_STRING_VALUE_TYPE)
		free(cson->value.string);
	free(cson->key);
	free(cson);
}

void	cson_free(t_cson *cson)
{
	while (cson->parent != NULL)
		cson = cson->parent;
	cson_eliminate(cson);
}
