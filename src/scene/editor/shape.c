/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightsource.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sceneeditor.h"
#include <assert.h>

void	scenebuffer_add_shape(t_scene *scene, t_shape *shape, t_bool is_child)
{
	shape->addr = scene->meta.shapes_size;
	if (shape->material_addr < 0 || shape->material_addr >= scene->meta.nmaterials)
		shape->material_addr = DEFAULT_MATERIAL_ID;
	if (shape->material_addr != DEFAULT_MATERIAL_ID)
		shape->material_addr *= sizeof(t_material);
	scenebuffer_append(scene, shape, sizeof(t_shape), SHAPEBUFF_TARGET);
	if (!is_child)
		scene->meta.nshapes++;
}
