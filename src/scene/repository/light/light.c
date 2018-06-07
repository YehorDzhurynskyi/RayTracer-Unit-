/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
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

static t_light_type	recognize_light_type(const char *type)
{
	if (ft_strequ(type, CSON_LIGHT_DIRECTIONAL))
		return (DIRLIGHT);
	else if (ft_strequ(type, CSON_LIGHT_POINT))
		return (POINTLIGHT);
	else if (ft_strequ(type, CSON_LIGHT_SPOT))
		return (SPOTLIGHT);
	print_error("The light type is missing or can not be recognized"); // TODO: print just message to console
	return (0);
}

t_light				deserialize_light(const t_cson *cson)
{
	t_light	light;

	light.color = deserialize_color(cson);
	light.intensity = cson_get_default_real(cson_valueof(cson,
	CSON_INTENSITY_KEY), 0.5);
	light.lighttype = recognize_light_type(cson_get_string(
		cson_valueof(cson, CSON_TYPE_KEY)));
	return (light);
}

t_cson				*serialize_light(t_cson *actual_light_cson, const t_light *light)
{
	cl_uchar4	color;

	color = light->color;
	cson_put(actual_light_cson, CSON_COLOR_KEY,
	serialize_color(&color));
	cson_put_real(actual_light_cson, CSON_INTENSITY_KEY,
	light->intensity);
	return (actual_light_cson);
}

static void			deserialize_actual_light(t_scene *scene,
t_light *light, const t_cson *cson)
{
	// TODO: add checking for errors
	if (light->lighttype == DIRLIGHT)
		scene_add_light(scene, light, (t_dirlight[]){deserialize_dirlight(cson)});
	else if (light->lighttype == POINTLIGHT)
		scene_add_light(scene, light, (t_pointlight[]){deserialize_pointlight(cson)});
	else if (light->lighttype == SPOTLIGHT)
		scene_add_light(scene, light, (t_spotlight[]){deserialize_spotlight(cson)});
}

t_err_code			deserialize_lights(t_scene *scene, const t_cson *cson)
{
	int				nlights;
	int				i;
	const t_cson	*light_cson;
	t_light			light;

	if (cson == NULL)
		return (SCENEREPOSITORY_NO_ERROR);
	if (cson_is_array(cson) == FALSE)
		return (SCENEREPOSITORY_WRONG_VALUE_FORMAT_ERROR);

	{ // TODO: map lightbuffer
		int err;
		scene->host_lightbuffer = clEnqueueMapBuffer(g_clcontext.command_queue, scene->lightbuffer,
		CL_TRUE, CL_MAP_WRITE, 0, sizeof(t_light) + sizeof(t_pointlight), 0, NULL, NULL, &err);
		if (err != CL_SUCCESS)
			print_opencl_error("Failed to map lightbuffer...", err);
	}

	nlights = cson_size(cson);
	i = 0;
	while (i < nlights)
	{
		light_cson = cson_at(cson, i++);
		light = deserialize_light(light_cson);
		deserialize_actual_light(scene, &light, light_cson);
	}
	// TODO: unmap lightbuffer
	scene_unmap(scene, LIGHT_BUFFER_TARGET);
	return (SCENEREPOSITORY_NO_ERROR);
}
