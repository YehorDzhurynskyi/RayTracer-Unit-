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
#include "logger.h"

#define INTENSITY		0.5
#define INTENSITY_STR	TO_STRING(INTENSITY)

static t_light_type	recognize_light_type(const char *type, t_err_code *err)
{
	if (ft_strequ(type, CSON_LIGHT_DIRECTIONAL))
		return (DIRLIGHT);
	else if (ft_strequ(type, CSON_LIGHT_POINT))
		return (POINTLIGHT);
	else if (ft_strequ(type, CSON_LIGHT_SPOT))
		return (SPOTLIGHT);
	*err = RT_NO_REQUIRED_VALUE_ERROR;
	log_error("The light type is missing or can not be recognized", *err);
	return (0);
}

t_light				deserialize_light(const t_cson *cson, t_err_code *err)
{
	t_light			light;
	const t_cson	*intensity_cson;

	light.color = deserialize_color(cson, err);
	intensity_cson = cson_valueof(cson, CSON_INTENSITY_KEY);
	if (intensity_cson == NULL || cson_is_real(intensity_cson) == FALSE)
	{
		log_notify("Light intensity is absent or is not real-type"
		" value, the value is set to " INTENSITY_STR " by default");
		light.intensity = INTENSITY;
	}
	else
		light.intensity = cson_get_real(intensity_cson);
	light.lighttype = recognize_light_type(cson_get_string(
		cson_valueof(cson, CSON_TYPE_KEY)), err);
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
t_light *light, const t_cson *cson, t_err_code *err)
{
	if (light->lighttype == DIRLIGHT)
		scene_add_light(scene, light, (t_dirlight[]){deserialize_dirlight(cson, err)});
	else if (light->lighttype == POINTLIGHT)
		scene_add_light(scene, light, (t_pointlight[]){deserialize_pointlight(cson, err)});
	else if (light->lighttype == SPOTLIGHT)
		scene_add_light(scene, light, (t_spotlight[]){deserialize_spotlight(cson, err)});
}

t_err_code			deserialize_lights(t_scene *scene, const t_cson *cson)
{
	int				nlights;
	int				i;
	const t_cson	*light_cson;
	t_light			light;
	t_err_code		err;

	if (cson == NULL)
		return (RT_NO_ERROR);
	if (cson_is_array(cson) == FALSE)
		return (RT_WRONG_VALUE_FORMAT_ERROR);
	err = RT_NO_ERROR;
	nlights = cson_size(cson);
	{ // TODO: map lightbuffer
		int err;
		scene->host_lightbuffer = clEnqueueMapBuffer(g_clcontext.command_queue, scene->lightbuffer,
		CL_TRUE, CL_MAP_WRITE, 0, (sizeof(t_light) + sizeof(t_pointlight)) * nlights, 0, NULL, NULL, &err);
		if (err != CL_SUCCESS)
		{
			log_error(opencl_get_error(err), RT_OPENCL_ERROR);
			return (RT_OPENCL_ERROR);
		}
	}
	i = 0;
	while (i < nlights)
	{
		light_cson = cson_at(cson, i++);
		light = deserialize_light(light_cson, &err);
		deserialize_actual_light(scene, &light, light_cson, &err);
	}
	// TODO: unmap lightbuffer
	scene_unmap(scene, LIGHT_BUFFER_TARGET);
	return (err);
}
