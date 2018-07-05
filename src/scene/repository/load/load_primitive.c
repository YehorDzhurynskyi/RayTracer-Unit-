/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_primitive.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepository.h"
#include "sceneeditor.h"

static t_err_code	load_actual_limitation(t_scene *scene, const t_cson *cson,
int target, t_limitation *limitation)
{
	t_err_code	err;
	const void	*actual_limitation;

	actual_limitation = NULL;
	err = RT_NO_ERROR;
	if (IS_AXIAL(limitation->limitation_type))
		actual_limitation = (t_axial_limitation[]){deserialize_axial_limitation(cson, &err)};
	else
		return (RT_WRONG_VALUE_TYPE_ERROR);
	scenebuffer_add_limitation(scene, limitation, actual_limitation, target);
	return (err);
}

static t_err_code	load_actual_primitive(t_scene *scene, const t_cson *cson,
int target, t_primitive *primitive)
{
	t_err_code	err;
	const void	*actual_primitive;

	err = RT_NO_ERROR;
	if (primitive->primitive_type == SPHERE)
		actual_primitive = (t_sphere[]){deserialize_sphere(cson, &err)};
	else if (primitive->primitive_type == CYLINDER)
		actual_primitive = (t_cylinder[]){deserialize_cylinder(cson, &err)};
	else if (primitive->primitive_type == CONE)
		actual_primitive = (t_cone[]){deserialize_cone(cson, &err)};
	else if (ZERO_SIZE_PRIMITIVE(primitive->primitive_type))
		actual_primitive = NULL;
	else
		return (RT_WRONG_VALUE_TYPE_ERROR);
	scenebuffer_add_primitive(scene, primitive, actual_primitive, target);
	return (err);
}

static t_err_code	load_limitations(t_scene *scene,
const t_cson *limitations_cson, int target)
{
	t_err_code		err;
	int				count;
	int				i;
	const t_cson	*limitation_cson;
	t_limitation	limitation;

	err = RT_NO_ERROR;
	count = cson_size(limitations_cson);
	i = 0;
	while (i < count)
	{
		limitation_cson = cson_at(limitations_cson, i++);
		limitation = deserialize_limitation(limitation_cson, &err);
		load_actual_limitation(scene, limitation_cson, target, &limitation);
	}
	return (err);
}

t_err_code			load_primitive(t_scene *scene, const t_cson *cson, int target)
{
	t_err_code		err;
	t_primitive		primitive;
	const t_cson	*limitations_cson;

	err = RT_NO_ERROR;
	if (cson == NULL)
		return (RT_VALUE_PARSING_ERROR);
	if (cson_is_object(cson) == FALSE)
		return (RT_WRONG_VALUE_FORMAT_ERROR);
	primitive = deserialize_primitive(cson, &err);
	limitations_cson = cson_valueof(cson, CSON_LIMITATIONS_KEY);
	primitive.nlimitations = limitations_cson == NULL ? 0 : cson_size(limitations_cson);
	load_actual_primitive(scene, cson, target, &primitive);
	if (limitations_cson != NULL)
		load_limitations(scene, limitations_cson, target);
	return (err);
}
