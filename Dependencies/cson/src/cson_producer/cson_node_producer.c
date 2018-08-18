/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_node_producer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson_producer.h"

size_t					cson_produce_indentation(t_cson_producer *producer,
int indent_depth)
{
	int		i;
	size_t	bytes_produced;

	bytes_produced = 0;
	i = 0;
	while (i++ < indent_depth)
		bytes_produced += cson_produce_bytes(producer, "\t", 1);
	return (bytes_produced);
}

static inline t_bool	cson_is_quoted_key(const char *key)
{
	while (*key)
	{
		if (!ft_isalnum(*key++))
			return (TRUE);
	}
	return (FALSE);
}

size_t					cson_produce_node(t_cson_producer *producer,
const t_cson *cson, int indent_depth)
{
	size_t	bytes_produced;
	t_bool	is_quoted_key;

	bytes_produced = cson_produce_indentation(producer, indent_depth);
	if (cson->key != NULL)
	{
		is_quoted_key = cson_is_quoted_key(cson->key);
		if (is_quoted_key)
			bytes_produced += cson_produce_bytes(producer, "\"", 1);
		bytes_produced += cson_produce_bytes(producer,
			cson->key, ft_strlen(cson->key));
		if (is_quoted_key)
			bytes_produced += cson_produce_bytes(producer, "\"", 1);
		bytes_produced += cson_produce_bytes(producer, ": ", 2);
	}
	if (cson_is_primitive(cson))
		bytes_produced += cson_produce_primitive_value(producer, cson);
	else if (cson_is_composite(cson))
		bytes_produced += cson_produce_composite_value(producer, cson,
			indent_depth);
	bytes_produced += cson_produce_bytes(producer, "\n", 1);
	return (bytes_produced);
}
