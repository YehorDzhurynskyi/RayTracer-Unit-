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
#include <assert.h>

#define AMBIENT		0.15
#define AMBIENT_STR	TO_STRING(AMBIENT)
#define FOV			60.0
#define FOV_STR		TO_STRING(FOV)

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

static t_aa					recognize_anti_aliasing(const char *type)
{
	if (ft_strequ(type, CSON_4xSSAA_KEY))
		return (SSAAx4);
	else if (ft_strequ(type, CSON_8xSSAA_KEY))
		return (SSAAx8);
	return (NOAA);
}

static size_t				get_approximate_item_size(t_buff_target target)
{
	if (target == SHAPEBUFF_TARGET)
		return (sizeof(t_shape) + sizeof(t_sphere));
	else if (target == LIGHTSOURCEBUFF_TARGET)
		return (sizeof(t_lightsource) + sizeof(t_pointlightsource));
	else if (target == MATERIALBUFF_TARGET)
		return (sizeof(t_material));
	assert("Unrecognized target" == NULL);
	return (0);
}

static t_load_item			get_load_item_callback(t_buff_target target)
{
	if (target == SHAPEBUFF_TARGET)
		return (load_shape);
	else if (target == LIGHTSOURCEBUFF_TARGET)
		return (load_lightsource);
	else if (target == MATERIALBUFF_TARGET)
		return (load_material);
	assert("Unrecognized target" == NULL);
	return (0);
}

static t_err_code			load_array(t_scene *scene, const t_cson *arr_cson,
t_buff_target target)
{
	int			count;
	int			i;
	t_err_code	err;
	size_t		approx_item_size;
	t_load_item	load_item;

	if (arr_cson == NULL)
		return (RT_NO_ERROR);
	if (cson_is_array(arr_cson) == FALSE)
		return (RT_WRONG_VALUE_FORMAT_ERROR);
	load_item = get_load_item_callback(target);
	approx_item_size = get_approximate_item_size(target);
	count = cson_size(arr_cson);
	scenebuffer_map(scene, 0, approx_item_size * count, target);
	err = RT_NO_ERROR;
	i = 0;
	while (i < count)
		err |= load_item(scene, cson_at(arr_cson, i++));
	scenebuffer_unmap(scene, target);
	return (err);
}

t_err_code					scene_load(t_scene *scene, const char *filename)
{
	t_cson		*scene_cson;
	t_err_code	err;

	scene_cson = cson_parse_file(filename, &err);
	if (err != 0)
		return (map_err_code(err));
	scene->config.trace_depth = cson_get_default_integer(
		cson_valueof(scene_cson, CSON_TRACE_DEPTH_KEY), 5);
	scene->config.aa = recognize_anti_aliasing(
		cson_get_string(cson_valueof(scene_cson, CSON_ANTI_ALIASING_KEY)));
	scene->config.global_illumination = cson_get_default_boolean(
		cson_valueof(scene_cson, CSON_GLOBAL_ILLU_KEY), FALSE);
	scene->config.ambient = deserialize_real(scene_cson,
	CSON_AMBIENT_KEY, AMBIENT, AMBIENT_STR);
	scene->config.fov = deserialize_real(scene_cson,
	CSON_FOV_KEY, FOV, FOV_STR);
	err = RT_NO_ERROR;
	err |= load_array(scene, cson_valueof(scene_cson, CSON_MATERIALS_KEY), MATERIALBUFF_TARGET);
	err |= load_array(scene, cson_valueof(scene_cson, CSON_LIGHTSOURCES_KEY), LIGHTSOURCEBUFF_TARGET);
	err |= load_array(scene, cson_valueof(scene_cson, CSON_SHAPES_KEY), SHAPEBUFF_TARGET);
	scene->camera = deserialize_camera(cson_valueof(scene_cson, CSON_CAMERA_KEY), &err);
	cson_free(scene_cson);
	return (err);
}
