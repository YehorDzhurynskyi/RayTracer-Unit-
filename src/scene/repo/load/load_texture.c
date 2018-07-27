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
	const void	*actual_texture;

	actual_texture = NULL;
	if (tex->texture_type == CHESS)
		actual_texture = (t_chess_texture[]){deserialize_chess_texture(tex_cson)};
	else if (tex->texture_type == CLIMAGE)
		actual_texture = (t_climage_texture[]){deserialize_climage_texture(scene, tex_cson)};
	scenebuffer_add_texture(scene, tex, actual_texture);
}

void	load_texture(t_scene *scene, const t_cson *cson)
{
	t_texture	texture;

	texture = deserialize_texture(cson);
	load_actual_texture(scene, cson, &texture);
}
