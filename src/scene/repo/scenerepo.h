/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scenerepo.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENEREPO_H
# define SCENEREPO_H

# include "cson.h"
# include "scene.h"
# include "shape.h"
# include "material.h"
# include "limitation.h"
# include "logger.h"
# include "lightsource.h"
# include "texture.h"

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
# define CSON_NEAR_RADIUS_KEY			"near_radius"
# define CSON_FAR_RADIUS_KEY			"far_radius"
# define CSON_ANGLE_KEY					"angle"
# define CSON_DIRECTION_KEY				"direction"
# define CSON_CHILDREN_KEY				"children"
# define CSON_COLOR_KEY					"color"

# define CSON_AMBIENT_KEY				"ambient"
# define CSON_FOV_KEY					"fov"
# define CSON_SKYBOX_KEY				"skybox"
# define CSON_GLOBAL_ILLU_KEY			"global_illumintaion"
# define CSON_ANTI_ALIASING_KEY			"anti_aliasing"
# define CSON_NOAA_KEY					"NOAA"
# define CSON_4xSSAA_KEY				"4xSSAA"
# define CSON_8xSSAA_KEY				"8xSSAA"
# define CSON_TRACE_DEPTH_KEY			"trace_depth"

# define CSON_MATERIALS_KEY				"materials"
# define CSON_MATERIAL_KEY				"material"
# define CSON_DIFFUSE_COLOR_KEY			"diffuse_color"
# define CSON_SPECULAR_COLOR_KEY		"specular_color"
# define CSON_DIFFUSE_TEXTURE_KEY		"diffuse_texture"
# define CSON_SPECULAR_TEXTURE_KEY		"specular_texture"
# define CSON_GLOSSINESS_KEY			"glossiness"
# define CSON_GLOSSINESS_TEXTURE_KEY	"glossiness_texture"
# define CSON_NORMAL_TEXTURE_KEY		"normal_map_texture"
# define CSON_IOR_KEY					"ior"

# define CSON_SHAPES_KEY				"shapes"
# define CSON_PRIMITIVE_KEY				"primitive"
# define CSON_SHAPE_COMPOSITE			"composite"
# define CSON_SHAPE_POINT				"point"
# define CSON_SHAPE_SPHERE				"sphere"
# define CSON_SHAPE_TORUS				"torus"
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
# define CSON_IS_RELATIVE_KEY			"is_relative"
# define CSON_CUTTING_KEY				"cutting"
# define CSON_APPLY_IF_LESS_KEY			"apply_if_less"
# define CSON_LIMIT_KEY					"limit"

# define CSON_X_AXIS_KEY				"x-axis"
# define CSON_Y_AXIS_KEY				"y-axis"
# define CSON_Z_AXIS_KEY				"z-axis"

# define CSON_TEXTURES_KEY				"textures"
# define CSON_TEXTURE_KEY				"texture"
# define CSON_SCALE_KEY					"scale"
# define CSON_UOFFSET_KEY				"u_offset"
# define CSON_VOFFSET_KEY				"v_offset"
# define CSON_COLOR1_KEY				"color1"
# define CSON_COLOR2_KEY				"color2"
# define CSON_URI_KEY					"uri"

# define CSON_TEXTURE_CHESS				"chess"
# define CSON_TEXTURE_RESOURCE			"resource"

void				load_scene(t_scene *scene, const t_cson *scene_cson);
void				scene_upload(const t_scene *scene, const char *filename);

typedef	void (*t_load_item)(t_scene*, const t_cson*);

void				load_material(t_scene *scene, const t_cson *cson);
void				load_lightsource(t_scene *scene, const t_cson *cson);
void				load_shape(t_scene *scene, const t_cson *cson);
void				load_primitive(t_scene *scene, const t_cson *cson, int target);
void				load_texture(t_scene *scene, const t_cson *cson);
void				load_cltextures(t_scene *scene);
cl_mem				load_skybox(const char *dirname);

/*
**	(de)serializing functions
*/
t_camera			deserialize_camera(const t_cson *cson);
void				deserialize_shapes(t_scene *scene, const t_cson *cson);
t_shape				deserialize_shape(const t_cson *cson);
t_primitive			deserialize_primitive(const t_cson *cson);
t_cone				deserialize_cone(const t_cson *cson);
t_cylinder			deserialize_cylinder(const t_cson *cson);
t_sphere			deserialize_sphere(const t_cson *cson);
t_torus				deserialize_torus(const t_cson *cson);
t_material			deserialize_material(const t_cson *cson);
t_limitation		deserialize_limitation(const t_cson *cson);
t_axial_limitation	deserialize_axial_limitation(const t_cson *cson);
void				deserialize_lights(t_scene *scene, const t_cson *cson);
t_lightsource		deserialize_lightsource(const t_cson *cson);
t_pointlightsource	deserialize_pointlightsource(const t_cson *cson);
t_dirlightsource	deserialize_dirlightsource(const t_cson *cson);
t_spotlightsource	deserialize_spotlightsource(const t_cson *cson);
t_texture			deserialize_texture(const t_cson *cson);
t_chess_texture		deserialize_chess_texture(const t_cson *cson);
t_climage_texture	deserialize_climage_texture(t_scene *scene, const t_cson *cson);
t_vec3d				deserialize_vec3d_required(const t_cson *cson, t_bool normalize);
t_vec3d				deserialize_vec3d_optional(const t_cson *cson, t_bool normalize, const t_vec3d default_value);
t_clvec3			deserialize_vec3_required(const t_cson *cson, t_bool normalize);
t_clvec3			deserialize_vec3_optional(const t_cson *cson, t_bool normalize, const t_vec3d default_value);
t_clcolor			deserialize_color_required(const t_cson *cson);
t_clcolor			deserialize_color_optional(const t_cson *cson, const t_clcolor default_color);
t_clscalar			deserialize_real_required(const t_cson *cson);
t_clscalar			deserialize_real_optional(const t_cson *cson, const t_clscalar default_value);
cl_int				deserialize_int_required(const t_cson *cson);
cl_int				deserialize_int_optional(const t_cson *cson, const cl_int default_value);
t_clbool			deserialize_bool_required(const t_cson *cson);
t_clbool			deserialize_bool_optional(const t_cson *cson, const t_clbool default_value);
t_clmat4x4			deserialize_orientation_required(const t_cson *cson);
t_clmat4x4			deserialize_orientation_optional(const t_cson *cson, const t_vec3d default_angles);

t_cson				*serialize_shape(const t_shape *shape);
t_cson				*serialize_camera(const t_camera *camera);
t_cson				*serialize_primitive(t_cson *actual_primitive_cson,
const t_primitive *primitive);
t_cson				*serialize_cone(const t_cone *cone);
t_cson				*serialize_cylinder(const t_cylinder *cylinder);
t_cson				*serialize_sphere(const t_sphere *sphere);
t_cson				*serialize_material(const t_material *material);
t_cson				*serialize_limitation(t_cson *actual_limitation_cson,
const t_limitation *limitation);
t_cson				*serialize_axial_limitation(t_cson *actual_limitation_cson,
const t_axial_limitation *axial_limitation);
t_cson				*serialize_lightsource(t_cson *actual_lightsource_cson,
const t_lightsource *lightsource);
t_cson				*serialize_pointlightsource(const t_pointlightsource *pointlightsource);
t_cson				*serialize_dirlightsource(const t_dirlightsource *dirlightsource);
t_cson				*serialize_spotlightsource(const t_spotlightsource *spotlightsource);
t_cson				*serialize_vec3(const t_clvec3 *vec);
t_cson				*serialize_color(const t_clcolor *color);

# define AMBIENT		0.1
# define FOV			60.0
# define INTENSITY		1.0
# define SPOT_ANGLE		20.0
# define LIMIT			0.0
# define IOR			1.0
# define ANGLE			15.0
# define RADIUS			1.0
# define SCALE			1.0
# define UOFFSET		0.0
# define VOFFSET		0.0

# define AMBIENT_STR	TO_STRING(AMBIENT)
# define FOV_STR		TO_STRING(FOV)
# define IOR_STR		TO_STRING(IOR)
# define SCALE_STR		TO_STRING(SCALE)
# define UOFFSET_STR	TO_STRING(UOFFSET)
# define VOFFSET_STR	TO_STRING(VOFFSET)

#endif
