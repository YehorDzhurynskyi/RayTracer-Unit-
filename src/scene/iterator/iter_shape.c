/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_shape.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sceneiterator.h"

t_iterator			shape_begin(const t_scene *scene)
{
	return ((t_iterator){scene->meta.nshapes, scene->host_shapebuffer});
}

const t_shape		*shape_next(t_iterator *iterator)
{
	const t_shape	*current;
	int				nchildren;
	t_iterator		limitation_iter;
	const t_shape	*child;

	current = (const t_shape*)iterator->current;
	nchildren = current->nchildren;
	while (nchildren-- >= 0)
	{
		iterator->current += sizeof(t_shape);
		limitation_iter = limitation_begin((const t_primitive*)
		iterator->current);
		while (has_next(&limitation_iter))
			limitation_next(&limitation_iter);
		iterator->current = limitation_iter.current;
		if (nchildren >= 0)
		{
			child = (const t_shape*)iterator->current;
			nchildren += child->nchildren;
		}
	}
	--iterator->count;
	return (current);
}

const t_primitive	*shape_get_primitive(const t_shape *shape)
{
	return ((const t_primitive*)++shape);
}

t_iterator			children_begin(const t_shape *shape)
{
	t_iterator limitation_iter;

	limitation_iter = limitation_begin(shape_get_primitive(shape));
	while (has_next(&limitation_iter))
		limitation_next(&limitation_iter);
	return ((t_iterator){shape->nchildren, limitation_iter.current});
}

const t_shape		*children_next(t_iterator *iterator)
{
	const t_shape	*current;
	t_iterator		limitation_iter;

	current = (const t_shape*)iterator->current;
	iterator->current += sizeof(t_shape);
	limitation_iter = limitation_begin((const t_primitive*)iterator->current);
	while (has_next(&limitation_iter))
		limitation_next(&limitation_iter);
	iterator->current = limitation_iter.current;
	--iterator->count;
	return (current);
}
