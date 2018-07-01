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

void	scenebuffer_map(t_scene *scene, int offset, size_t size, t_buff_target target);
void	scenebuffer_unmap(t_scene *scene, t_buff_target target);

void	scenebuffer_append(t_scene *scene,
const void *data, size_t size, t_buff_target target);

void	scenebuffer_add_lightsource(t_scene *scene,
t_lightsource *lightsource, const void *actuial_lightsource);
void	scenebuffer_add_primitive(t_scene *scene, const t_primitive *primitive,
const void *actual_primitive, t_buff_target target);
void	scenebuffer_add_material(t_scene *scene, t_material *material);
void	scenebuffer_add_shape(t_scene *scene, t_shape *shape, t_bool is_child);
void	scenebuffer_add_limitation(t_scene *scene, const t_limitation *limitation,
const void *actual_limitation, t_buff_target target);

#endif
