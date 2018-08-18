/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepo.h"
#include "sceneeditor.h"

static void	load_actual_texture(t_scene *scene,
const t_cson *tex_cson, t_texture *tex)
{
	const void			*actual_texture;
	t_chess_texture		chess_texture;
	t_climage_texture	climage_texture;
	t_perlin_texture	perlin_texture;

	actual_texture = NULL;
	if (tex->texture_type == CHESS)
	{
		chess_texture = deserialize_chess_texture(tex_cson);
		actual_texture = &chess_texture;
	}
	else if (tex->texture_type == CLIMAGE)
	{
		climage_texture = deserialize_climage_texture(scene, tex_cson);
		actual_texture = &climage_texture;
	}
	else if (tex->texture_type == PERLIN)
	{
		perlin_texture = deserialize_perlin_texture(tex_cson);
		actual_texture = &perlin_texture;
	}
	scenebuffer_add_texture(scene, tex, actual_texture);
}

void		load_texture(t_scene *scene, const t_cson *cson)
{
	t_texture	texture;

	texture = deserialize_texture(cson);
	load_actual_texture(scene, cson, &texture);
}
