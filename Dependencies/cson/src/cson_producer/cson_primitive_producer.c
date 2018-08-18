/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_primitive_producer.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson_producer.h"
#include <stdlib.h>

static inline void		trail_zeroes(char *value)
{
	char	*end;

	end = value + ft_strlen(value) - 1;
	while (*end == '0')
		end--;
	*(end + 1 + (*end == '.')) = '\0';
}

static size_t			cson_produce_number(t_cson_producer *producer,
const t_cson *cson)
{
	char	*value;
	size_t	bytes_produced;

	bytes_produced = 0;
	value = NULL;
	if (cson_is_integer(cson))
		value = ft_itoa(cson_get_integer(cson));
	else if (cson_is_real(cson))
	{
		value = ft_ldtoa(cson_get_real(cson), 15);
		trail_zeroes(value);
	}
	bytes_produced += cson_produce_bytes(producer, value, ft_strlen(value));
	free(value);
	return (bytes_produced);
}

size_t					cson_produce_primitive_value(t_cson_producer *producer,
const t_cson *cson)
{
	size_t	bytes_produced;
	char	*str;

	bytes_produced = 0;
	if (cson_is_integer(cson) || cson_is_real(cson))
	{
		bytes_produced += cson_produce_number(producer, cson);
	}
	else
	{
		if (cson_is_boolean(cson))
		{
			str = cson_get_boolean(cson) ? "true" : "false";
			bytes_produced += cson_produce_bytes(producer, str, ft_strlen(str));
		}
		if (cson_is_string(cson))
		{
			bytes_produced += cson_produce_bytes(producer, "\"", 1);
			str = (char*)cson_get_string(cson);
			bytes_produced += cson_produce_bytes(producer, str, ft_strlen(str));
			bytes_produced += cson_produce_bytes(producer, "\"", 1);
		}
	}
	return (bytes_produced);
}
