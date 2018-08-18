/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_builder_composite.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson.h"

t_cson	*cson_array(void)
{
	t_cson	*cson;

	cson = cson_alloc(NULL);
	cson->value_type = CSON_ARRAY_VALUE_TYPE;
	cson->value.tuple = alst_create(4);
	return (cson);
}

t_cson	*cson_object(void)
{
	t_cson	*cson;

	cson = cson_alloc(NULL);
	cson->value_type = CSON_OBJECT_VALUE_TYPE;
	cson->value.tuple = alst_create(4);
	return (cson);
}
