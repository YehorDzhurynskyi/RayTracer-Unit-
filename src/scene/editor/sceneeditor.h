/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sceneeditor.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENEEDITOR_H
# define SCENEEDITOR_H

# include "scene.h"
# include "shape.h"
# include "material.h"
# include "limitation.h"
# include "lightsource.h"
# include "texture.h"

void				scenebuffer_map(t_scene *scene, int offset, size_t size,
t_buff_target target);
void				scenebuffer_unmap(t_scene *scene, t_buff_target target);

void				scenebuffer_put(t_scene *scene, const void *data,
int offset, size_t size);
void				scenebuffer_append(t_scene *scene,
const void *data, size_t size, t_buff_target target);

void				scenebuffer_add_lightsource(t_scene *scene,
t_lightsource *lightsource, const void *actuial_lightsource);
void				scenebuffer_add_primitive(t_scene *scene, const t_primitive
*primitive, const void *actual_primitive, t_buff_target target);
void				scenebuffer_add_material(t_scene *scene,
t_material *material);
void				scenebuffer_add_shape(t_scene *scene,
t_shape *shape, t_bool is_child);
void				scenebuffer_add_limitation(t_scene *scene,
const t_limitation *limitation, const void *actual_limitation,
t_buff_target target);
void				scenebuffer_add_texture(t_scene *scene,
t_texture *texture, const void *actual_texture);

void				scenebuffer_update_material(t_scene *scene,
const t_material *material);

t_vec3d				scenebuffer_default_position(void);
t_shape				scenebuffer_default_shape(void);
t_primitive			scenebuffer_default_primitive(void);
t_sphere			scenebuffer_default_sphere(void);
t_cylinder			scenebuffer_default_cylinder(void);
t_cone				scenebuffer_default_cone(void);
t_spotlightsource	scenebuffer_default_spotlightsource(void);
t_pointlightsource	scenebuffer_default_pointlightsource(void);
t_dirlightsource	scenebuffer_default_dirlightsource(void);
t_lightsource		scenebuffer_default_lightsource(void);
t_material			scenebuffer_default_material(void);

#endif
