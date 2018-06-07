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
# include "light.h"

/*
**	SHAPE EDITING
*/
void				scene_add_shape(t_scene *scene, t_shape *shape,
const void *actual_shape);
void				scene_update_shape(t_scene *scene, const t_shape *shape,
const void *actual_shape);
void				scene_remove_shape(t_scene *scene, const t_shape *shape);

/*
**	LIGHT EDITING
*/
void				scene_add_light(t_scene *scene, t_light *light,
const void *actual_light);
void				scene_update_light(t_scene *scene, const t_light *light,
const void *actual_light);
void				scene_remove_light(t_scene *scene, const t_light *light);

#endif
