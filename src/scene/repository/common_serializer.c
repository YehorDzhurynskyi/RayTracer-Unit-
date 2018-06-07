/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_serializer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepository.h"

t_cson	*serialize_vec3d(const t_vec3d *vec)
{
	t_cson	*cson;

	cson = cson_array();
	cson_push_real(cson, vec->x);
	cson_push_real(cson, vec->y);
	cson_push_real(cson, vec->z);
	return (cson);
}

t_cson	*serialize_vec4(const t_clvec4 *vec)
{
	t_cson	*cson;

	cson = cson_array();
	cson_push_real(cson, vec->x);
	cson_push_real(cson, vec->y);
	cson_push_real(cson, vec->z);
	cson_push_real(cson, vec->w);
	return (cson);
}

t_cson	*serialize_color(const cl_uchar4 *color)
{
	unsigned int	uicolor;

	uicolor = color->w << 24;
	uicolor |= color->x << 16;
	uicolor |= color->y << 8;
	uicolor |= color->z << 0;
	return (cson_string(ft_hex_uitoa(uicolor, TRUE, FALSE)));
}
