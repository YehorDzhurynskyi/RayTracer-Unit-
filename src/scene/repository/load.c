/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
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

#define AMBIENT		0.15
#define AMBIENT_STR	TO_STRING(AMBIENT)

static inline t_err_code	map_err_code(int err)
{
	if (err == CSON_MEM_ALLOC_ERROR)
		return (RT_MEM_ALLOC_ERROR);
	else if (err == CSON_FILE_OPENING_ERROR)
		return (RT_FILE_OPENING_ERROR);
	else if (err == CSON_FILE_READING_ERROR)
		return (RT_FILE_READING_ERROR);
	else if (err == CSON_KEY_PARSING_ERROR)
		return (RT_KEY_PARSING_ERROR);
	else if (err == CSON_VALUE_PARSING_ERROR)
		return (RT_VALUE_PARSING_ERROR);
	else if (err == CSON_BRACKETS_PARSING_ERROR)
		return (RT_BRACKETS_PARSING_ERROR);
	else if (err == CSON_EMPTY_DATA_PARSING_ERROR)
		return (RT_EMPTY_DATA_PARSING_ERROR);
	else if (err == CSON_NULL_PARAMETER_ERROR)
		return (RT_NULL_PARAMETER_ERROR);
	return (RT_UNDEFINED_ERROR);
}

t_err_code					scene_load(t_scene *scene, const char *filename)
{
	t_cson			*scene_cson;
	t_err_code		err;
	const t_cson	*ambient_cson;

	scene_cson = cson_parse_file(filename, &err);
	if (err != 0)
		return (map_err_code(err));
	ambient_cson = cson_valueof(scene_cson, CSON_AMBIENT_KEY);
	if (ambient_cson == NULL || cson_is_real(ambient_cson) == FALSE)
	{
		log_notify("Scene ambient intensity is absent or is not real-type"
		" value, the value is set to " AMBIENT_STR " by default");
		scene->ambient = AMBIENT;
	}
	else
		scene->ambient = cson_get_real(ambient_cson);
	err = RT_NO_ERROR;
	err |= deserialize_shapes(scene,
	cson_valueof(scene_cson, CSON_SHAPES_KEY));
	err |= deserialize_lights(scene,
	cson_valueof(scene_cson, CSON_LIGHTS_KEY));
	scene->camera = deserialize_camera(
	cson_valueof(scene_cson, CSON_CAMERA_KEY), &err);
	cson_free(scene_cson);
	return (err);
}
