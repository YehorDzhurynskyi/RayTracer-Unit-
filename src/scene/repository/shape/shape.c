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
#include "logger.h"

#define SHININESS			20.0
#define SHININESS_STR		TO_STRING(SHININESS)
#define REFLECTIVITY		0.0
#define REFLECTIVITY_STR	TO_STRING(REFLECTIVITY)
#define IOR					1.0
#define IOR_STR				TO_STRING(IOR)
#define OPACITY				1.0
#define OPACITY_STR			TO_STRING(OPACITY)

static t_shape_type	recognize_shape_type(const char *type, t_err_code *err)
{
	if (ft_strequ(type, CSON_SHAPE_SPHERE))
		return (SPHERE);
	else if (ft_strequ(type, CSON_SHAPE_PLANE))
		return (PLANE);
	else if (ft_strequ(type, CSON_SHAPE_CONE))
		return (CONE);
	else if (ft_strequ(type, CSON_SHAPE_CYLINDER))
		return (CYLINDER);
	// TODO: print just message to console
	*err = RT_NO_REQUIRED_VALUE_ERROR;
	log_error("The shape type is missing or can not be recognized", *err);
	return (0);
}

t_shape				deserialize_shape(const t_cson *cson, t_err_code *err)
{
	t_shape			shape;
	const t_cson	*position_cson;
	const t_cson	*shininess_cson;
	const t_cson	*reflectivity_cson;
	const t_cson	*ior_cson;
	const t_cson	*opacity_cson;

	position_cson = cson_valueof(cson, CSON_POSITION_KEY);
	if (position_cson == NULL)
	{
		*err = RT_NO_REQUIRED_VALUE_ERROR;
		log_error("Shape's position vector is absent", *err);
		return ((t_shape){});
	}
	shape.position = deserialize_vec4(position_cson, FALSE, err);
	shape.color = deserialize_color(cson, err);
	shininess_cson = cson_valueof(cson, CSON_SHININESS_KEY);
	if (shininess_cson == NULL || cson_is_real(shininess_cson) == FALSE)
	{
		log_notify("Shape's shininess is absent or is not real-type"
		" value, the value is set to " SHININESS_STR " by default");
		shape.shininess = SHININESS;
	}
	else
		shape.shininess = cson_get_real(shininess_cson);
	reflectivity_cson = cson_valueof(cson, CSON_REFLECTIVITY_KEY);
	if (reflectivity_cson == NULL || cson_is_real(reflectivity_cson) == FALSE)
	{
		log_notify("Shape's reflectivity is absent or is not "
		"real-type value, the value is set to " REFLECTIVITY_STR " by default");
		shape.reflectivity = REFLECTIVITY;
	}
	else
		shape.reflectivity = cson_get_real(reflectivity_cson);
	ior_cson = cson_valueof(cson, CSON_IOR_KEY);
	if (ior_cson == NULL || cson_is_real(ior_cson) == FALSE)
	{
		log_notify("Shape's index of refraction (IOR) is absent or is not "
		"real-type value, the value is set to " IOR_STR " by default");
		shape.ior = IOR;
	}
	else
		shape.ior = cson_get_real(ior_cson);
	opacity_cson = cson_valueof(cson, CSON_OPACITY_KEY);
	if (opacity_cson == NULL || cson_is_real(opacity_cson) == FALSE)
	{
		log_notify("Shape's opacity is absent or is not "
		"real-type value, the value is set to " OPACITY_STR " by default");
		shape.opacity = OPACITY;
	}
	else
		shape.opacity = cson_get_real(opacity_cson);
	shape.shapetype = recognize_shape_type(cson_get_string(
		cson_valueof(cson, CSON_TYPE_KEY)), err);
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
	cson_put_real(actual_shape_cson, CSON_IOR_KEY,
	shape->ior);
	cson_put_real(actual_shape_cson, CSON_OPACITY_KEY,
	shape->opacity);
	return (actual_shape_cson);
}

static void			deserialize_actual_shape(t_scene *scene,
t_shape *shape, const t_cson *cson, t_err_code *err)
{
	if (shape->shapetype == PLANE)
		scene_add_shape(scene, shape, (t_plane[]){deserialize_plane(cson, err)});
	else if (shape->shapetype == SPHERE)
		scene_add_shape(scene, shape, (t_sphere[]){deserialize_sphere(cson, err)});
	else if (shape->shapetype == CONE)
		scene_add_shape(scene, shape, (t_cone[]){deserialize_cone(cson, err)});
	else if (shape->shapetype == CYLINDER)
		scene_add_shape(scene, shape, (t_cylinder[]){deserialize_cylinder(cson, err)});
}

t_err_code			deserialize_shapes(t_scene *scene, const t_cson *cson)
{
	int				nshapes;
	int				i;
	const t_cson	*shape_cson;
	t_shape			shape;
	t_err_code		err;

	if (cson == NULL)
		return (RT_NO_ERROR);
	if (cson_is_array(cson) == FALSE)
		return (RT_WRONG_VALUE_FORMAT_ERROR);
	err = RT_NO_ERROR;
	nshapes = cson_size(cson);
	{ // TODO: map shapebuffer
		int err;
		scene->host_shapebuffer = clEnqueueMapBuffer(g_clcontext.command_queue, scene->shapebuffer,
		CL_TRUE, CL_MAP_WRITE, 0, (sizeof(t_shape) + sizeof(t_sphere)) * nshapes, 0, NULL, NULL, &err);
		if (err != CL_SUCCESS)
		{
			log_error(opencl_get_error(err), RT_OPENCL_ERROR);
			return (RT_OPENCL_ERROR);
		}
	}
	i = 0;
	while (i < nshapes)
	{
		shape_cson = cson_at(cson, i++);
		shape = deserialize_shape(shape_cson, &err);
		deserialize_actual_shape(scene, &shape, shape_cson, &err);
	}
	// TODO: unmap shapebuffer
	scene_unmap(scene, SHAPE_BUFFER_TARGET);
	return (err);
}
