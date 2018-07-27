/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repo_climage_texture.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepo.h"
#include "sceneeditor.h"

t_climage_texture	deserialize_climage_texture(t_scene *scene, const t_cson *cson)
{
	t_climage_texture	tex;

	tex.tex_index = scene->texture_map.data.size;
	texture_map_add(&scene->texture_map, cson_get_string(cson_valueof(cson, CSON_URI_KEY)));
	return (tex);
}
