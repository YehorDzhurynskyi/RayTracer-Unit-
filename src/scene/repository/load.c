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

static inline t_err_code	map_err_code(int err)
{
	if (err == CSON_MEM_ALLOC_ERROR)
		return (SCENEREPOSITORY_MEM_ALLOC_ERROR);
	else if (err == CSON_FILE_OPENING_ERROR)
		return (SCENEREPOSITORY_FILE_OPENING_ERROR);
	else if (err == CSON_FILE_READING_ERROR)
		return (SCENEREPOSITORY_FILE_READING_ERROR);
	else if (err == CSON_KEY_PARSING_ERROR)
		return (SCENEREPOSITORY_KEY_PARSING_ERROR);
	else if (err == CSON_VALUE_PARSING_ERROR)
		return (SCENEREPOSITORY_VALUE_PARSING_ERROR);
	else if (err == CSON_BRACKETS_PARSING_ERROR)
		return (SCENEREPOSITORY_BRACKETS_PARSING_ERROR);
	else if (err == CSON_EMPTY_DATA_PARSING_ERROR)
		return (SCENEREPOSITORY_EMPTY_DATA_PARSING_ERROR);
	else if (err == CSON_NULL_PARAMETER_ERROR)
		return (SCENEREPOSITORY_NULL_PARAMETER_ERROR);
	return (SCENEREPOSITORY_UNDEFINED_ERROR);
}

t_err_code					scene_load(t_scene *scene, const char *filename)
{
	const t_cson	*scene_cson;
	t_err_code		err;

	scene_cson = cson_parse_file(filename, &err);
	if (err != 0)
		return (map_err_code(err));
	scene->ambient = cson_get_default_real(
	cson_valueof(scene_cson, CSON_AMBIENT_KEY), 0.15);
	err = SCENEREPOSITORY_NO_ERROR;
	err |= deserialize_shapes(scene,
	cson_valueof(scene_cson, CSON_SHAPES_KEY));
	err |= deserialize_lights(scene,
	cson_valueof(scene_cson, CSON_LIGHTS_KEY));
	scene->camera = deserialize_camera(
	cson_valueof(scene_cson, CSON_CAMERA_KEY));
	return (err);
}
