/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sceneiterator.h"

t_iterator		texture_begin(const t_scene *scene)
{
	return ((t_iterator){scene->meta.ntextures, scene->host_texturebuffer});
}

const t_texture	*texture_next(t_iterator *iterator)
{
	const t_texture	*current;

	current = (const t_texture*)iterator->current;
	iterator->current = (const t_byte*)(current + 1);
	if (current->texture_type == CHESS)
		iterator->current += sizeof(t_chess_texture);
	else if (current->texture_type == CLIMAGE)
		iterator->current += sizeof(t_climage_texture);
	else if (current->texture_type == PERLIN)
		iterator->current += sizeof(t_perlin_texture);
	--iterator->count;
	return (current);
}
