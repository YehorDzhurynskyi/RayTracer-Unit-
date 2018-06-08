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
#include "logger.h"

t_vec3d			deserialize_vec3d(const t_cson *cson, t_bool normalize, t_err_code *err)
{
	t_vec3d	res;

	if (cson_is_array(cson) == FALSE || cson_size(cson) != 3)
	{
		*err = cson_is_array(cson) == FALSE
		? RT_WRONG_VALUE_FORMAT_ERROR : RT_WRONG_DIMENSION_ERROR;
		log_error("Invalid vector-3 represantation, "
		"it should be real-value array of size 3", *err);
		return ((t_vec3d){0.0, 0.0, 0.0});
	}
	res.x = cson_get_real(cson_at(cson, 0));
	res.y = cson_get_real(cson_at(cson, 1));
	res.z = cson_get_real(cson_at(cson, 2));
	if (normalize)
	{
		if (vec3d_length(&res) <= 1.0E-6f)
		{
			*err = RT_ZERO_LENGTH_VECTOR_ERROR;
			log_error("This vector should has length > 0", *err);
			return (res);
		}
		res = vec3d_normalize(&res);
	}
	return (res);
}

t_clvec4		deserialize_vec4(const t_cson *cson, t_bool normalize, t_err_code *err)
{
	t_clvec4	res;
	t_vec3d		vec;

	vec = deserialize_vec3d(cson, normalize, err);
	res = (t_clvec4){{vec.x, vec.y, vec.z, 0.0}};
	return (res);
}

static t_bool	validate_color_str(const char *colorstr, t_err_code *err)
{
	unsigned int	count;

	if (colorstr[0] == '0' && (colorstr[1] == 'x' || colorstr[1] == 'X'))
		colorstr += 2;
	count = 0;
	while (*colorstr)
	{
		if (ft_ishex(*colorstr++) == FALSE)
		{
			*err = RT_WRONG_VALUE_FORMAT_ERROR;
			log_error("Invalid symbol in color string", *err);
			return (FALSE);
		}
		++count;
	}
	if (count != 6 && count != 8)
	{
		*err = RT_WRONG_DIMENSION_ERROR;
		log_error("Invalid dimension of hex value color, it should be either 6 or 8", *err);
		return (FALSE);
	}
	return (TRUE);
}

cl_uchar4		deserialize_color(const t_cson *cson, t_err_code *err)
{
	unsigned int	hex;
	cl_uchar4		color;
	const t_cson	*color_cson;

	color_cson = cson_valueof(cson, CSON_COLOR_KEY);
	if (color_cson == NULL || cson_is_string(color_cson) == FALSE)
	{
		*err = color_cson == NULL ? RT_NO_REQUIRED_VALUE_ERROR : RT_WRONG_VALUE_FORMAT_ERROR;
		log_error("Color is absent or has wrong value format, "
		"it should be a string of hex color representation", *err);
		return ((cl_uchar4){});
	}
	if (validate_color_str(cson_get_string(color_cson), err) == FALSE)
		return ((cl_uchar4){});
	hex = ft_hex_atoui(cson_get_string(color_cson));
	color.x = (hex >> 16) & 0xFF;
	color.y = (hex >> 8) & 0xFF;
	color.z = (hex >> 0) & 0xFF;
	color.w = (hex >> 24) & 0xFF;
	return (color);
}
