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
# include "material.h"
# include "limitation.h"
# include "lightsource.h"
# include "logger.h"

/*
**	cson keys for scene (de)serializer
*/
# define CSON_CAMERA_KEY				"camera"
# define CSON_POSITION_KEY				"position"
# define CSON_ORIENTATION_KEY			"orientation"
# define CSON_UP_KEY					"up"
# define CSON_RIGHT_KEY					"right"
# define CSON_FORWARD_KEY				"forward"
# define CSON_SPOT_KEY					"spot"

# define CSON_TYPE_KEY					"type"

# define CSON_RELATION_KEY				"relation"
# define CSON_RELATION_UNION_KEY		"union"
# define CSON_RELATION_INTERSECTION_KEY	"intersection"
# define CSON_RELATION_NEGATION_KEY		"negation"

# define CSON_RADIUS_KEY				"radius"
# define CSON_ANGLE_KEY					"angle"
# define CSON_DIRECTION_KEY				"direction"
# define CSON_CHILDREN_KEY				"children"
# define CSON_COLOR_KEY					"color"

# define CSON_AMBIENT_KEY				"ambient"
# define CSON_FOV_KEY					"fov"
# define CSON_GLOBAL_ILLU_KEY			"global illumintaion"
# define CSON_ANTI_ALIASING_KEY			"anti aliasing"
# define CSON_NOAA_KEY					"NOAA"
# define CSON_4xSSAA_KEY				"4xSSAA"
# define CSON_8xSSAA_KEY				"8xSSAA"
# define CSON_TRACE_DEPTH_KEY			"trace depth"

# define CSON_MATERIALS_KEY				"materials"
# define CSON_MATERIAL_KEY				"material"
# define CSON_DIFFUSE_COLOR_KEY			"diffuse color"
# define CSON_SPECULAR_COLOR_KEY		"specular color"
# define CSON_SPECULARITY_KEY			"specularity"
# define CSON_GLOSSINESS_KEY			"glossiness"
# define CSON_OPACITY_KEY				"opacity"
# define CSON_IOR_KEY					"ior"

# define CSON_SHAPES_KEY				"shapes"
# define CSON_PRIMITIVE_KEY				"primitive"
# define CSON_SHAPE_COMPOSITE			"composite"
# define CSON_SHAPE_POINT				"point"
# define CSON_SHAPE_SPHERE				"sphere"
# define CSON_SHAPE_PLANE				"plane"
# define CSON_SHAPE_CONE				"cone"
# define CSON_SHAPE_CYLINDER			"cylinder"

# define CSON_LIGHTSOURCES_KEY			"lightsources"
# define CSON_LIGHT_DIRECTIONAL			"directional"
# define CSON_LIGHT_POINT				"point"
# define CSON_LIGHT_SPOT				"spot"

# define CSON_INTENSITY_KEY				"intensity"
# define CSON_ATTENUATION_KEY			"attenuation"

# define CSON_LIMITATIONS_KEY			"limitations"
# define CSON_IS_RELATIVE_KEY			"is relative"
# define CSON_CUTTING_KEY				"cutting"
# define CSON_APPLY_IF_LESS_KEY			"apply if less"
# define CSON_LIMIT_KEY					"limit"

# define CSON_X_AXIS_KEY				"x-axis"
# define CSON_Y_AXIS_KEY				"y-axis"
# define CSON_Z_AXIS_KEY				"z-axis"

t_err_code			scene_load(t_scene *scene, const char *filename);
t_err_code			scene_upload(const t_scene *scene, const char *filename);

typedef	t_err_code (*t_load_item)(t_scene*, const t_cson*);

t_err_code			load_material(t_scene *scene, const t_cson *cson);
t_err_code			load_lightsource(t_scene *scene, const t_cson *cson);
t_err_code			load_shape(t_scene *scene, const t_cson *cson);
t_err_code			load_primitive(t_scene *scene, const t_cson *cson, int target);

/*
**	(de)serializing functions
*/
t_camera			deserialize_camera(const t_cson *cson, t_err_code *err);
t_cson				*serialize_camera(const t_camera *camera);

t_err_code			deserialize_shapes(t_scene *scene, const t_cson *cson);
t_shape				deserialize_shape(const t_cson *cson, t_err_code *err);
t_cson				*serialize_shape(const t_shape *shape);
t_primitive			deserialize_primitive(const t_cson *cson, t_err_code *err);
t_cson				*serialize_primitive(t_cson *actual_primitive_cson,
const t_primitive *primitive);
t_cone				deserialize_cone(const t_cson *cson, t_err_code *err);
t_cson				*serialize_cone(const t_cone *cone);
t_cylinder			deserialize_cylinder(const t_cson *cson, t_err_code *err);
t_cson				*serialize_cylinder(const t_cylinder *cylinder);
t_sphere			deserialize_sphere(const t_cson *cson, t_err_code *err);
t_cson				*serialize_sphere(const t_sphere *sphere);

t_material			deserialize_material(const t_cson *cson, t_err_code *err);
t_cson				*serialize_material(const t_material *material);

t_limitation		deserialize_limitation(const t_cson *cson, t_err_code *err);
t_cson				*serialize_limitation(t_cson *actual_limitation_cson,
const t_limitation *limitation);
t_axial_limitation	deserialize_axial_limitation(const t_cson *cson, t_err_code *err);
t_cson				*serialize_axial_limitation(t_cson *actual_limitation_cson,
const t_axial_limitation *axial_limitation);

t_err_code			deserialize_lights(t_scene *scene, const t_cson *cson);
t_lightsource		deserialize_lightsource(const t_cson *cson, t_err_code *err);
t_cson				*serialize_lightsource(t_cson *actual_lightsource_cson,
const t_lightsource *lightsource);
t_pointlightsource	deserialize_pointlightsource(const t_cson *cson, t_err_code *err);
t_cson				*serialize_pointlightsource(const t_pointlightsource *pointlightsource);
t_dirlightsource	deserialize_dirlightsource(const t_cson *cson, t_err_code *err);
t_cson				*serialize_dirlightsource(const t_dirlightsource *dirlightsource);
t_spotlightsource	deserialize_spotlightsource(const t_cson *cson, t_err_code *err);
t_cson				*serialize_spotlightsource(const t_spotlightsource *spotlightsource);

# define RT_VEC_REPO_NORMALIZE	1
# define RT_VEC_REPO_REQUIRED	2

t_vec3d				deserialize_vec3d(const t_cson *cson,
const char *key, int mask, t_err_code *err);
t_clvec3			deserialize_vec3(const t_cson *cson,
const char *key, int mask, t_err_code *err);
t_cson				*serialize_vec3(const t_clvec3 *vec);
t_clcolor			deserialize_color(const t_cson *cson, const char *key,
t_err_code *err);
t_cson				*serialize_color(const t_clcolor *color);
t_clscalar			deserialize_real(const t_cson *cson, const char *key,
const t_clscalar default_value, const char *default_value_str);
t_clmat4x4			deserialize_orientation(const t_cson *cson,
t_err_code *err);

/*
**	This prototype is required because of norminette
*/
t_err_code			load_shape_data(t_scene *scene, const t_cson *cson,
t_bool is_child);

#endif
