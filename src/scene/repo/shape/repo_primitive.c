/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repo_primitive.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepo.h"

static t_primitive_type	recognize_primitive_type(const char *type)
{
	if (ft_strequ(type, CSON_SHAPE_COMPOSITE))
		return (COMPOSITE);
	else if (ft_strequ(type, CSON_SHAPE_POINT))
		return (POINT);
	else if (ft_strequ(type, CSON_SHAPE_SPHERE))
		return (SPHERE);
	else if (ft_strequ(type, CSON_SHAPE_PLANE))
		return (PLANE);
	else if (ft_strequ(type, CSON_SHAPE_CONE))
		return (CONE);
	else if (ft_strequ(type, CSON_SHAPE_CYLINDER))
		return (CYLINDER);
	else if (ft_strequ(type, CSON_SHAPE_TORUS))
		return (TORUS);
	else if (ft_strequ(type, CSON_SHAPE_QUADRIC))
		return (QUADRIC);
	else if (ft_strequ(type, CSON_SHAPE_PARALLELEPIPED))
		return (PARALLELEPIPED);
	return (0);
}

t_primitive				deserialize_primitive(const t_cson *cson)
{
	t_primitive	primitive;

	primitive.position = deserialize_vec3_required(cson_valueof(cson,
	CSON_POSITION_KEY), FALSE);
	primitive.orientation = deserialize_orientation_optional(cson,
	(t_vec3d){0.0, 0.0, 0.0});
	primitive.primitive_type = recognize_primitive_type(cson_get_string(
		cson_valueof(cson, CSON_TYPE_KEY)));
	primitive.nlimitations = 0;
	return (primitive);
}
