/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sceneiterator.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENEITERATOR_H
# define SCENEITERATOR_H

typedef struct
{
	int						count;
	__constant t_byte		*current;
}	t_iterator;

t_iterator					shape_begin(const t_scene *scene, const t_scene_buffers *buffers);
t_iterator					lightsource_begin(const t_scene *scene, const t_scene_buffers *buffers);
t_iterator					limitation_begin(__constant t_primitive *primitive);
t_iterator					children_begin(__constant t_shape *shape);

__constant t_shape			*shape_next(t_iterator *iterator);
__constant t_lightsource	*lightsource_next(t_iterator *iterator);
__constant t_limitation		*limitation_next(t_iterator *iterator);
__constant t_shape			*children_next(t_iterator *iterator);

t_bool						has_next(const t_iterator *iterator);

__constant t_primitive		*shape_get_primitive(__constant t_shape *shape);
__constant t_byte			*primitive_get_actual(__constant t_primitive *primitive);
__constant t_byte			*lightsource_get_actual(__constant t_lightsource *lightsource);
__constant t_byte			*limitation_get_actual(__constant t_limitation *limitation);

#endif
