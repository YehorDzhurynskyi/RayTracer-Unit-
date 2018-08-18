/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_material.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sceneeditor.h"

void	scenebuffer_add_material(t_scene *scene, t_material *material)
{
	material->addr = scene->meta.materials_size;
	scenebuffer_append(scene, material, sizeof(t_material),
	MATERIALBUFF_TARGET);
	scene->meta.nmaterials++;
}

void	scenebuffer_update_material(t_scene *scene, const t_material *material)
{
	scenebuffer_put(scene, (void*)material, material->addr, sizeof(t_material));
}
