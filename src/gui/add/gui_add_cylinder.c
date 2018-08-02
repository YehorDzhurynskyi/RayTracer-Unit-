/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_add_cylinder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sceneeditor.h"
#include "logger.h"

void	gui_add_cylinder(void)
{
	t_shape		shape;
	t_primitive	primitive;
	t_cylinder	cylinder;

	shape = scenebuffer_default_shape();
	primitive = scenebuffer_default_primitive();
	cylinder = scenebuffer_default_cylinder();
	primitive.primitive_type = CYLINDER;
	scenebuffer_map(&g_main_scene, g_main_scene.meta.shapes_size,
	sizeof(t_shape) + sizeof(t_primitive) + sizeof(t_cylinder), SHAPEBUFF_TARGET);
	scenebuffer_add_shape(&g_main_scene, &shape, FALSE);
	scenebuffer_add_primitive(&g_main_scene, &primitive, &cylinder, SHAPEBUFF_TARGET);
	scenebuffer_unmap(&g_main_scene, SHAPEBUFF_TARGET);
	log_notify("Cylinder was added to scene");
}
