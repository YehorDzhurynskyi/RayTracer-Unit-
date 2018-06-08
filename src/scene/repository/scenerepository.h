/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scenerepository.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENEREPOSITORY_H
# define SCENEREPOSITORY_H

# include "cson.h"
# include "scene.h"
# include "shape.h"
# include "light.h"
# include "logger.h"

/*
**	cson keys for scene (de)serializer
*/
# define CSON_CAMERA_KEY		"camera"
# define CSON_POSITION_KEY		"position"
# define CSON_UP_KEY			"up"
# define CSON_RIGHT_KEY			"right"
# define CSON_FORWARD_KEY		"forward"
# define CSON_SPOT_KEY			"spot"

# define CSON_TYPE_KEY			"type"
# define CSON_COLOR_KEY			"color"

# define CSON_SHAPES_KEY		"shapes"
# define CSON_SHAPE_SPHERE		"sphere"
# define CSON_SHAPE_PLANE		"plane"
# define CSON_SHAPE_CONE		"cone"
# define CSON_SHAPE_CYLINDER	"cylinder"

# define CSON_RADIUS_KEY		"radius"
# define CSON_ANGLE_KEY			"angle"
# define CSON_NORMAL_KEY		"normal"
# define CSON_DIRECTION_KEY		"direction"
# define CSON_SHININESS_KEY		"shininess"
# define CSON_REFLECTIVITY_KEY	"reflectivity"

# define CSON_AMBIENT_KEY		"ambient"

# define CSON_LIGHTS_KEY		"lights"
# define CSON_LIGHT_DIRECTIONAL	"directional"
# define CSON_LIGHT_POINT		"point"
# define CSON_LIGHT_SPOT		"spot"

# define CSON_INTENSITY_KEY		"intensity"
# define CSON_ATTENUATION_KEY	"attenuation"

t_err_code		scene_load(t_scene *scene, const char *filename);
t_err_code		scene_upload(const t_scene *scene, const char *filename);

/*
**	(de)serializing functions
*/
t_clvec4		deserialize_vec4(const t_cson *cson, t_bool normalize, t_err_code *err);
t_cson			*serialize_vec4(const t_clvec4 *vec);
t_vec3d			deserialize_vec3d(const t_cson *cson, t_bool normalize, t_err_code *err);
t_cson			*serialize_vec3d(const t_vec3d *vec);
cl_uchar4		deserialize_color(const t_cson *cson, t_err_code *err);
t_cson			*serialize_color(const cl_uchar4 *color);

t_camera		deserialize_camera(const t_cson *cson, t_err_code *err);
t_cson			*serialize_camera(const t_camera *camera);

t_err_code		deserialize_shapes(t_scene *scene, const t_cson *cson);
t_shape			deserialize_shape(const t_cson *cson, t_err_code *err);
t_cson			*serialize_shape(t_cson *actual_shape_cson,
const t_shape *shape);
t_cone			deserialize_cone(const t_cson *cson, t_err_code *err);
t_cson			*serialize_cone(const t_cone *cone);
t_cylinder		deserialize_cylinder(const t_cson *cson, t_err_code *err);
t_cson			*serialize_cylinder(const t_cylinder *cylinder);
t_plane			deserialize_plane(const t_cson *cson, t_err_code *err);
t_cson			*serialize_plane(const t_plane *plane);
t_sphere		deserialize_sphere(const t_cson *cson, t_err_code *err);
t_cson			*serialize_sphere(const t_sphere *sphere);

t_err_code		deserialize_lights(t_scene *scene, const t_cson *cson);
t_light			deserialize_light(const t_cson *cson, t_err_code *err);
t_cson			*serialize_light(t_cson *actual_light_cson,
const t_light *light);
t_pointlight	deserialize_pointlight(const t_cson *cson, t_err_code *err);
t_cson			*serialize_pointlight(const t_pointlight *pointlight);
t_dirlight		deserialize_dirlight(const t_cson *cson, t_err_code *err);
t_cson			*serialize_dirlight(const t_dirlight *dirlight);
t_spotlight		deserialize_spotlight(const t_cson *cson, t_err_code *err);
t_cson			*serialize_spotlight(const t_spotlight *spotlight);

#endif
