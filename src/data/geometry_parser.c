/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"
#include "parser.h"
#include "error.h"

void	parse_basic_geometry(t_geometry *geom, const t_cson *geom_cson)
{
	const t_cson	*prty_cson;

	geom->color = parse_cson_color(geom_cson);
	prty_cson = cson_valueof(geom_cson, CSON_GLOSSINESS_KEY);
	geom->glossiness = prty_cson == NULL ? 0.0 : cson_get_real(prty_cson);
	prty_cson = cson_valueof(geom_cson, CSON_SHININESS_KEY);
	geom->shininess = prty_cson == NULL ? 0.0 : cson_get_real(prty_cson);
	prty_cson = cson_valueof(geom_cson, CSON_POSITION_KEY);
	geom->pos = prty_cson == NULL ?
	(t_vec3d){0.0, 0.0, 0.0} : parse_vec3d(prty_cson);
	prty_cson = cson_valueof(geom_cson, CSON_REFLECTIVITY_KEY);
	geom->reflectivity = prty_cson == NULL ? 0.0 : cson_get_real(prty_cson);
}

void	parse_geometries(t_scene *scene, const t_cson *cson)
{
	int				i;
	int				size;
	const t_cson	*geom_cson;
	const t_cson	*primitive_cson;
	const char		*primitive;

	size = cson_size(cson);
	i = 0;
	while (i < size)
	{
		geom_cson = cson_at(cson, i++);
		primitive_cson = cson_valueof(geom_cson, CSON_PRIMITIVE_KEY);
		primitive = cson_get_string(primitive_cson);
		if (ft_strequ(primitive, CSON_PRIMITIVE_SPHERE))
			parse_sphere(scene, geom_cson);
		else if (ft_strequ(primitive, CSON_PRIMITIVE_PLANE))
			parse_plane(scene, geom_cson);
		else if (ft_strequ(primitive, CSON_PRIMITIVE_CYLINDER))
			parse_cylinder(scene, geom_cson);
		else if (ft_strequ(primitive, CSON_PRIMITIVE_CONE))
			parse_cone(scene, geom_cson);
		else
			print_error("Scene parsing error: unrecognized geometry primitive");
	}
}
