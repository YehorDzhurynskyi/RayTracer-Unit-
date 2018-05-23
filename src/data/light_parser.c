/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"
#include "dirlight.h"
#include "pointlight.h"
#include "spotlight.h"
#include "parser.h"
#include "error.h"

void	parse_basic_light(t_light *light, const t_cson *cson)
{
	const t_cson	*prty_cson;

	prty_cson = cson_valueof(cson, CSON_INTENSITY_KEY);
	light->intensity = prty_cson == NULL ? 1.0 : cson_get_real(prty_cson);
	light->color = parse_cson_color(cson);
}

void	parse_lights(t_scene *scene, const t_cson *cson)
{
	int				i;
	int				size;
	const t_cson	*light_cson;
	const t_cson	*type_cson;
	const char		*type;

	size = cson_size(cson);
	i = 0;
	while (i < size)
	{
		light_cson = cson_at(cson, i++);
		type_cson = cson_valueof(light_cson, CSON_TYPE_KEY);
		type = cson_get_string(type_cson);
		if (ft_strequ(type, CSON_LIGHT_DIRECTIONAL))
			parse_dirlight(scene, light_cson);
		else if (ft_strequ(type, CSON_LIGHT_POINT))
			parse_pointlight(scene, light_cson);
		else if (ft_strequ(type, CSON_LIGHT_SPOT))
			parse_spotlight(scene, light_cson);
		else
			print_error("Scene parsing error: unrecognized light type");
	}
}
