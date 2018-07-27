/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include <assert.h>

t_texture_map	texture_map_create(int capacity)
{
	t_texture_map	map;

	alst_init(&map.data, capacity);
	return (map);
}

const char		*texture_map_at(const t_texture_map *map, int index)
{
	assert(index >= 0 && index < (int)map->data.size);
	return (alst_get((t_alst*)&map->data, index));
}

void			texture_map_add(t_texture_map *map, const char *value)
{
	alst_add(&map->data, ft_strdup(value));
}

void			texture_map_cleanup(t_texture_map *map)
{
	alst_clear(&map->data, ft_memdel);
	ft_memdel((void**)&map->data.array);
}
