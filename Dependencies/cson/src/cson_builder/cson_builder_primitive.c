/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_builder_primitive.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson.h"

t_cson	*cson_integer(int value)
{
	t_cson	*cson;

	cson = cson_alloc(NULL);
	cson->value_type = CSON_INTEGER_VALUE_TYPE;
	cson->value.integer = value;
	return (cson);
}

t_cson	*cson_real(double value)
{
	t_cson	*cson;

	cson = cson_alloc(NULL);
	cson->value_type = CSON_REAL_VALUE_TYPE;
	cson->value.real = value;
	return (cson);
}

t_cson	*cson_boolean(t_bool value)
{
	t_cson	*cson;

	cson = cson_alloc(NULL);
	cson->value_type = CSON_BOOLEAN_VALUE_TYPE;
	cson->value.boolean = value;
	return (cson);
}

t_cson	*cson_string(const char *value)
{
	t_cson	*cson;

	cson = cson_alloc(NULL);
	cson->value_type = CSON_STRING_VALUE_TYPE;
	cson->value.string = ft_strdup(value);
	return (cson);
}
