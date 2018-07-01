/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
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
	if (count != 8)
	{
		*err = RT_WRONG_DIMENSION_ERROR;
		log_error("Invalid dimension of hex value color, it should be 8 (ARGB)", *err);
		return (FALSE);
	}
	return (TRUE);
}

t_clcolor		deserialize_color(const t_cson *cson, const char *key, t_err_code *err)
{
	unsigned int	hex;
	t_clcolor			color;
	const t_cson	*color_cson;

	color_cson = cson_valueof(cson, key);
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

t_cson	*serialize_color(const t_clcolor *color)
{
	unsigned int	uicolor;

	uicolor = color->w << 24;
	uicolor |= color->x << 16;
	uicolor |= color->y << 8;
	uicolor |= color->z << 0;
	return (cson_string(ft_hex_uitoa(uicolor, TRUE, FALSE)));
}
