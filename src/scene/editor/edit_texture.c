/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sceneeditor.h"
#include <assert.h>

static size_t	texture_size(t_texture_type type)
{
	if (type == CHESS)
		return (sizeof(t_chess_texture));
	else if (type == CLIMAGE)
		return (sizeof(t_climage_texture));
	else if (type == WAVE)
		return (0);
	else if (type == PERLIN)
		return (sizeof(t_perlin_texture));
	assert(FALSE && "Texture structure instance should"
	" have texture_type field");
	return (0);
}

void			scenebuffer_add_texture(t_scene *scene,
t_texture *texture, const void *actual_texture)
{
	texture->addr = scene->meta.textures_size;
	scenebuffer_append(scene, texture, sizeof(t_texture), TEXTUREBUFF_TARGET);
	if (actual_texture != NULL)
		scenebuffer_append(scene, actual_texture,
		texture_size(texture->texture_type), TEXTUREBUFF_TARGET);
	scene->meta.ntextures++;
}
