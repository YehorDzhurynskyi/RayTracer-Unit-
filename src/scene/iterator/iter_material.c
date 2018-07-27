/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_material.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sceneiterator.h"

t_iterator			material_begin(const t_scene *scene)
{
	return ((t_iterator){scene->meta.nmaterials, scene->host_materialbuffer});
}

const t_material	*material_next(t_iterator *iterator)
{
	const t_material	*current;

	current = (const t_material*)iterator->current;
	iterator->current += sizeof(t_material);
	--iterator->count;
	return (current);
}