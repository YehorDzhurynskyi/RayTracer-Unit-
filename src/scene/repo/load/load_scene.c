/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepo.h"
#include "sceneeditor.h"
#include "sceneiterator.h"
#include "logger.h"
#include <assert.h>

static t_aa		recognize_anti_aliasing(const char *type)
{
	if (ft_strequ(type, CSON_4XSSAA_KEY))
		return (SSAAx4);
	else if (ft_strequ(type, CSON_8XSSAA_KEY))
		return (SSAAx8);
	return (NOAA);
}

static size_t	get_approximate_item_size(t_buff_target target)
{
	if (target == SHAPEBUFF_TARGET)
		return (sizeof(t_shape) + sizeof(t_sphere));
	else if (target == LIGHTSOURCEBUFF_TARGET)
		return (sizeof(t_lightsource) + sizeof(t_pointlightsource));
	else if (target == MATERIALBUFF_TARGET)
		return (sizeof(t_material));
	else if (target == TEXTUREBUFF_TARGET)
		return (sizeof(t_texture) + sizeof(t_climage_texture));
	assert("Unrecognized target" == NULL);
	return (0);
}

static void		load_array(t_scene *scene, const t_cson *arr_cson,
t_buff_target target)
{
	int				count;
	int				i;
	size_t			approx_item_size;
	const t_cson	*cson_item;

	approx_item_size = get_approximate_item_size(target);
	count = cson_size(arr_cson);
	scenebuffer_map(scene, 0, approx_item_size * count, target);
	i = 0;
	while (i < count)
	{
		cson_item = cson_at(arr_cson, i++);
		if (target == TEXTUREBUFF_TARGET)
			load_texture(scene, cson_item);
		else if (target == MATERIALBUFF_TARGET)
			load_material(scene, cson_item);
		else if (target == SHAPEBUFF_TARGET)
			load_shape(scene, cson_item);
		else if (target == LIGHTSOURCEBUFF_TARGET)
			load_lightsource(scene, cson_item);
	}
	scenebuffer_unmap(scene, target);
}

void			load_scene(t_scene *scene, const t_cson *scene_cson)
{
	scene_rewind(scene);
	scene->config.trace_depth = cson_get_default_integer(
		cson_valueof(scene_cson, CSON_TRACE_DEPTH_KEY), 5);
	scene->config.aa = recognize_anti_aliasing(
		cson_get_string(cson_valueof(scene_cson, CSON_ANTI_ALIASING_KEY)));
	scene->config.ambient = deserialize_real_optional(
		cson_valueof(scene_cson, CSON_AMBIENT_KEY), AMBIENT);
	scene->config.fov = deserialize_real_optional(
		cson_valueof(scene_cson, CSON_FOV_KEY), FOV);
	scene->texture_map = texture_map_create(
		cson_size(cson_valueof(scene_cson, CSON_TEXTURES_KEY)));
	load_array(scene, cson_valueof(scene_cson,
	CSON_TEXTURES_KEY), TEXTUREBUFF_TARGET);
	load_array(scene, cson_valueof(scene_cson,
	CSON_MATERIALS_KEY), MATERIALBUFF_TARGET);
	load_array(scene, cson_valueof(scene_cson,
	CSON_SHAPES_KEY), SHAPEBUFF_TARGET);
	load_array(scene, cson_valueof(scene_cson,
	CSON_LIGHTSOURCES_KEY), LIGHTSOURCEBUFF_TARGET);
	scene->camera = deserialize_camera(
		cson_valueof(scene_cson, CSON_CAMERA_KEY));
	scene->skybox = load_skybox(cson_get_string(
		cson_valueof(scene_cson, CSON_SKYBOX_KEY)));
	load_cltextures(scene);
	express_addresses_from_indices(scene);
}
