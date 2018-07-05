/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepository.h"

t_cson		*serialize_primitive(t_cson *actual_primitive_cson,
const t_primitive *primitive)
{
	(void)actual_primitive_cson;
	(void)primitive;
	return (NULL);
}

static t_primitive_type	recognize_primitive_type(const char *type, t_err_code *err)
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
	*err = RT_NO_REQUIRED_VALUE_ERROR;
	log_error("The primitive type is missing or can not be recognized", *err);
	return (0);
}

t_primitive	deserialize_primitive(const t_cson *cson, t_err_code *err)
{
	t_primitive	primitive;

	primitive.position = deserialize_vec3(cson, CSON_POSITION_KEY,
	RT_VEC_REPO_REQUIRED, err);
	primitive.orientation = deserialize_orientation(cson, err);
	primitive.primitive_type = recognize_primitive_type(cson_get_string(
		cson_valueof(cson, CSON_TYPE_KEY)), err);
	primitive.nlimitations = 0;
	return (primitive);
}
