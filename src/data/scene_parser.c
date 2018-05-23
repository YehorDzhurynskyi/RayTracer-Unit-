/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "parser.h"
#include "error.h"

static void	parse_camera(t_scene *scene, const t_cson *cson_cam)
{
	t_vec3d	pos;
	t_vec3d	spot;
	t_vec3d	up;

	pos = parse_vec3d(cson_valueof(cson_cam, CSON_POSITION_KEY));
	spot = parse_vec3d(cson_valueof(cson_cam, CSON_SPOT_KEY));
	up = parse_vec3d(cson_valueof(cson_cam, CSON_UP_KEY));
	camera_look_at(&scene->cam, &pos, &spot, &up);
}

static void	cson_deserialize(t_scene *scene, const t_cson *cson)
{
	const t_cson	*cson_cam;
	const t_cson	*cson_geometry;
	const t_cson	*cson_light;

	cson_cam = cson_valueof(cson, CSON_CAMERA_KEY);
	if (cson_cam != NULL)
		parse_camera(scene, cson_cam);
	cson_geometry = cson_valueof(cson, CSON_GEOMETRY_KEY);
	if (cson_geometry != NULL)
		parse_geometries(scene, cson_geometry);
	cson_light = cson_valueof(cson, CSON_LIGHT_KEY);
	if (cson_light != NULL)
		parse_lights(scene, cson_light);
}

t_scene		*scene_parse_from_cson(const char *csonfile)
{
	t_cson	*cson;
	int		err;
	t_scene	*scene;

	cson = cson_parse_file(csonfile, &err);
	if (err != 0)
		print_error("Error: Invalid cson file");
	scene = scene_alloc();
	cson_deserialize(scene, cson);
	cson_free(cson);
	return (scene);
}
