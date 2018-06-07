/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_deserializer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "scenerepository.h"

t_vec3d		deserialize_vec3d(const t_cson *cson, t_bool normalize)
{
	t_vec3d	res;

	if (cson_is_array(cson) == FALSE)
		return ((t_vec3d){0.0, 0.0, 0.0});
	res.x = cson_get_real(cson_at(cson, 0));
	res.y = cson_get_real(cson_at(cson, 1));
	res.z = cson_get_real(cson_at(cson, 2));
	if (normalize)
		res = vec3d_normalize(&res);
	return (res);
}

t_clvec4	deserialize_vec4(const t_cson *cson, t_bool normalize)
{
	t_clvec4	res;
	t_vec3d		vec;

	if (cson_is_array(cson) == FALSE)
		return ((t_clvec4){{0.0f, 0.0f, 0.0f, 0.0f}});
	vec = deserialize_vec3d(cson, normalize);
	res = (t_clvec4){{vec.x, vec.y, vec.z, 0.0}};
	return (res);
}

cl_uchar4	deserialize_color(const t_cson *cson)
{
	unsigned int	hex;
	cl_uchar4		color;
	
	hex = ft_hex_atoui(cson_get_default_string(
		cson_valueof(cson, CSON_COLOR_KEY), "0x00ffffff"));
	ft_printf("hex: %X\n", hex);
	color.x = (hex >> 16) & 0xFF;
	color.y = (hex >> 8) & 0xFF;
	color.z = (hex >> 0) & 0xFF;
	color.w = (hex >> 24) & 0xFF;
	// return ((cl_uchar4){{0xff, 0x0, 0xff, 0x0}});
	return (color);
}
