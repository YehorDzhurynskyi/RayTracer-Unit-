/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_add_material.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 17:34:37 by pzubar            #+#    #+#             */
/*   Updated: 2018/05/29 17:34:39 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sceneeditor.h"
#include "logger.h"

void	gui_add_material(void)
{
	t_material	material;

	material = scenebuffer_default_material();
	scenebuffer_map(&g_main_scene, g_main_scene.meta.materials_size,
	sizeof(t_material), MATERIALBUFF_TARGET);
	scenebuffer_add_material(&g_main_scene, &material);
	scenebuffer_unmap(&g_main_scene, MATERIALBUFF_TARGET);
	log_notify("Material was added to scene");
}
