/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepository.h"
#include "sceneeditor.h"
#include "error.h"

static t_shape_type	recognize_shape_type(const char *type)
{
	if (ft_strequ(type, CSON_SHAPE_SPHERE))
		return (SPHERE);
	else if (ft_strequ(type, CSON_SHAPE_PLANE))
		return (PLANE);
	else if (ft_strequ(type, CSON_SHAPE_CONE))
		return (CONE);
	else if (ft_strequ(type, CSON_SHAPE_CYLINDER))
		return (CYLINDER);
	print_error("The shape type is missing or can not be recognized"); // TODO: print just message to console
	return (0);
}

t_shape				deserialize_shape(const t_cson *cson)
{
	t_shape	shape;

	shape.position = deserialize_vec4(cson_valueof(cson,
	CSON_POSITION_KEY), FALSE);
	shape.color = deserialize_color(cson);
	shape.shininess = cson_get_default_real(cson_valueof(cson,
	CSON_SHININESS_KEY), 20.0);
	shape.reflectivity = cson_get_default_real(cson_valueof(cson,
	CSON_REFLECTIVITY_KEY), 0.0);
	shape.shapetype = recognize_shape_type(cson_get_string(
		cson_valueof(cson, CSON_TYPE_KEY)));
	return (shape);
}

t_cson				*serialize_shape(t_cson *actual_shape_cson, const t_shape *shape)
{
	t_clvec4	position;
	cl_uchar4	color;

	position = shape->position;
	color = shape->color;
	cson_put(actual_shape_cson, CSON_POSITION_KEY,
	serialize_vec4(&position));
	cson_put(actual_shape_cson, CSON_COLOR_KEY,
	serialize_color(&color));
	cson_put_real(actual_shape_cson, CSON_SHININESS_KEY,
	shape->shininess);
	cson_put_real(actual_shape_cson, CSON_REFLECTIVITY_KEY,
	shape->reflectivity);
	return (actual_shape_cson);
}

static void			deserialize_actual_shape(t_scene *scene,
t_shape *shape, const t_cson *cson)
{
	// TODO: add checking for errors
	if (shape->shapetype == PLANE)
		scene_add_shape(scene, shape, (t_plane[]){deserialize_plane(cson)});
	else if (shape->shapetype == SPHERE)
		scene_add_shape(scene, shape, (t_sphere[]){deserialize_sphere(cson)});
	else if (shape->shapetype == CONE)
		scene_add_shape(scene, shape, (t_cone[]){deserialize_cone(cson)});
	else if (shape->shapetype == CYLINDER)
		scene_add_shape(scene, shape, (t_cylinder[]){deserialize_cylinder(cson)});
}

t_err_code			deserialize_shapes(t_scene *scene, const t_cson *cson)
{
	int				nshapes;
	int				i;
	const t_cson	*shape_cson;
	t_shape			shape;

	if (cson == NULL)
		return (SCENEREPOSITORY_NO_ERROR);
	if (cson_is_array(cson) == FALSE)
		return (SCENEREPOSITORY_WRONG_VALUE_FORMAT_ERROR);
	nshapes = cson_size(cson);
	{ // TODO: map shapebuffer
		int err;
		scene->host_shapebuffer = clEnqueueMapBuffer(g_clcontext.command_queue, scene->shapebuffer,
		CL_TRUE, CL_MAP_WRITE, 0, (sizeof(t_shape) + sizeof(t_sphere)) * nshapes, 0, NULL, NULL, &err);
		if (err != CL_SUCCESS)
			print_opencl_error("Failed to map shapebuffer...", err);
	}
	i = 0;
	while (i < nshapes)
	{
		shape_cson = cson_at(cson, i++);
		shape = deserialize_shape(shape_cson);
		deserialize_actual_shape(scene, &shape, shape_cson);
	}
	// TODO: unmap shapebuffer
	scene_unmap(scene, SHAPE_BUFFER_TARGET);
	return (SCENEREPOSITORY_NO_ERROR);
}
