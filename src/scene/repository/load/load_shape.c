/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepository.h"
#include "sceneeditor.h"

static t_err_code	load_children(t_scene *scene, const t_cson *cson)
{
	int			i;
	int			count;
	t_err_code	err;

	err = RT_NO_ERROR;
	if (cson_is_array(cson) == FALSE)
		return (RT_WRONG_VALUE_FORMAT_ERROR);
	count = cson_size(cson);
	i = 0;
	while (i < count)
		err |= load_shape_data(scene, cson_at(cson, i++), TRUE);
	return (err);
}

t_err_code			load_shape(t_scene *scene, const t_cson *cson)
{
	return (load_shape_data(scene, cson, FALSE));
}

t_err_code			load_shape_data(t_scene *scene, const t_cson *cson,
t_bool is_child)
{
	t_err_code		err;
	t_shape			shape;
	const t_cson	*primitive_cson;
	const t_cson	*children_cson;

	err = RT_NO_ERROR;
	if (cson == NULL)
		return (RT_VALUE_PARSING_ERROR);
	if (cson_is_object(cson) == FALSE)
		return (RT_WRONG_VALUE_FORMAT_ERROR);
	shape = deserialize_shape(cson, &err);
	children_cson = cson_valueof(cson, CSON_CHILDREN_KEY);
	shape.nchildren = children_cson == NULL ? 0 : cson_size(children_cson);
	scenebuffer_add_shape(scene, &shape, is_child);
	primitive_cson = cson_valueof(cson, CSON_PRIMITIVE_KEY);
	if (primitive_cson == NULL)
		return (RT_NO_REQUIRED_VALUE_ERROR);
	load_primitive(scene, primitive_cson, SHAPEBUFF_TARGET);
	if (children_cson != NULL)
		err |= load_children(scene, children_cson);
	return (err);
}
