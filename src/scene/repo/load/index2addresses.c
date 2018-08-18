/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index2addresses.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepo.h"
#include "sceneiterator.h"
#include <assert.h>
#include "sceneeditor.h"

static int	texture_index2address(t_scene *scene, int index)
{
	t_iterator		texture_iter;
	const t_texture	*texture;

	texture_iter = texture_begin(scene);
	while (has_next(&texture_iter))
	{
		texture = texture_next(&texture_iter);
		if (index-- == 0)
			return (texture->addr);
	}
	assert("Wrong index this should be handled on validation stage" == NULL);
	return (-1);
}

void		express_addresses_from_indices(t_scene *scene)
{
	t_iterator	material_iter;
	t_material	*material;

	material_iter = material_begin(scene);
	scenebuffer_map(scene, 0, sizeof(t_material)
	* scene->meta.nmaterials, MATERIALBUFF_TARGET);
	while (has_next(&material_iter))
	{
		material = (t_material*)material_next(&material_iter);
		if (DIFFUSE_IS_TEX(material->mask))
			material->diffuse_albedo.tex_addr = texture_index2address(scene,
			material->diffuse_albedo.tex_addr);
		if (SPECULAR_IS_TEX(material->mask))
			material->specular_albedo.tex_addr = texture_index2address(scene,
			material->specular_albedo.tex_addr);
		if (GLOSSINESS_IS_TEX(material->mask))
			material->glossiness.tex_addr = texture_index2address(scene,
			material->glossiness.tex_addr);
		if (HAS_NORMAL_MAP(material->mask))
			material->normal_map = texture_index2address(scene,
			material->normal_map);
		scenebuffer_update_material(scene, material);
	}
	scenebuffer_unmap(scene, MATERIALBUFF_TARGET);
}
