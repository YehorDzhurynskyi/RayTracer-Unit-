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

# include "scene.h"
# include "shape.h"
# include "lightsource.h"
# include "limitation.h"
# include "material.h"

typedef struct
{
	int				count;
	const t_byte	*current;
}	t_iterator;

t_iterator			shape_begin(const t_scene *scene);
t_iterator			lightsource_begin(const t_scene *scene);
t_iterator			material_begin(const t_scene *scene);
t_iterator			limitation_begin(const t_primitive *primitive);

const t_shape		*shape_next(t_iterator *iterator);
const t_lightsource	*lightsource_next(t_iterator *iterator);
const t_material	*material_next(t_iterator *iterator);
const t_limitation	*limitation_next(t_iterator *iterator);

t_bool				has_next(const t_iterator *iterator);

const t_primitive	*shape_get_primitive(const t_shape *shape);
const t_primitive	*lightsource_get_primitive(const t_lightsource *lightsource);
const t_byte		*primitive_get_actual(const t_primitive *primitive);
const t_byte		*lightsource_get_actual(const t_lightsource *lightsource);
const t_byte		*limitation_get_actual(const t_limitation *limitation);

#endif
