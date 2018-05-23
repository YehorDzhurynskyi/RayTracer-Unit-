/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_vec3d	parse_vec3d(const t_cson *cson)
{
	t_vec3d			res;
	const t_cson	*value;

	value = cson_at(cson, 0);
	if (value == NULL)
		return ((t_vec3d){0.0, 0.0, 0.0});
	res.x = cson_get_real(value);
	value = cson_at(cson, 1);
	res.y = cson_get_real(value);
	value = cson_at(cson, 2);
	res.z = cson_get_real(value);
	return (res);
}

t_color	parse_cson_color(const t_cson *cson)
{
	const t_cson	*prty_cson;

	prty_cson = cson_valueof(cson, CSON_COLOR_KEY);
	return (prty_cson == NULL
	? 0x00FFFFFF : ft_hex_atoui(cson_get_string(prty_cson)));
}
