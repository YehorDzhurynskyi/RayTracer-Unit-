/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repo_lightsource.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepo.h"
#include "sceneeditor.h"

static t_lightsource_type	recognize_lightsource_type(const char *type)
{
	if (ft_strequ(type, CSON_LIGHT_DIRECTIONAL))
		return (DIRLIGHT);
	else if (ft_strequ(type, CSON_LIGHT_POINT))
		return (POINTLIGHT);
	else if (ft_strequ(type, CSON_LIGHT_SPOT))
		return (SPOTLIGHT);
	return (0);
}

t_lightsource				deserialize_lightsource(const t_cson *cson)
{
	t_lightsource	lightsource;

	lightsource.color = deserialize_color_required(cson_valueof(cson, CSON_COLOR_KEY));
	lightsource.intensity = deserialize_real_required(cson_valueof(cson, CSON_INTENSITY_KEY));
	lightsource.lightsource_type = recognize_lightsource_type(cson_get_string(
		cson_valueof(cson, CSON_TYPE_KEY)));
	return (lightsource);
}

t_cson						*serialize_light(t_cson *actual_lightsource_cson,
const t_lightsource *lightsource)
{
	t_clcolor	color;

	color = lightsource->color;
	cson_put(actual_lightsource_cson, CSON_COLOR_KEY,
	serialize_color(&color));
	cson_put_real(actual_lightsource_cson, CSON_INTENSITY_KEY,
	lightsource->intensity);
	return (actual_lightsource_cson);
}
