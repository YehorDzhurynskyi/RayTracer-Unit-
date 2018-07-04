/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightsource.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sceneiterator.h"

t_iterator			lightsource_begin(const t_scene *scene)
{
	return ((t_iterator){scene->meta.nlightsources, scene->host_lightsourcebuffer});
}

const t_lightsource	*lightsource_next(t_iterator *iterator)
{
	const t_lightsource	*current = (const t_lightsource*)iterator->current;
	iterator->current = lightsource_skip(current);
	if (current->lightsource_type == POINTLIGHT || current->lightsource_type == SPOTLIGHT)
	{
		t_iterator limitation_iter = limitation_begin((const t_primitive*)iterator->current);
		while (has_next(&limitation_iter))
			limitation_next(&limitation_iter);
		iterator->current = limitation_iter.current;
	}
	--iterator->count;
	return (current);}

const t_byte		*lightsource_get_actual(const t_lightsource *lightsource)
{
	return ((const t_byte*)++lightsource);
}
