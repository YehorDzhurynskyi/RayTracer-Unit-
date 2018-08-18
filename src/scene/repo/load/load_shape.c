/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepo.h"
#include "sceneeditor.h"

static void	load_shape_data(t_scene *scene, const t_cson *cson,
t_bool is_child)
{
	t_shape			shape;
	const t_cson	*primitive_cson;
	const t_cson	*children_cson;
	int				i;
	int				count;

	shape = deserialize_shape(cson);
	children_cson = cson_valueof(cson, CSON_CHILDREN_KEY);
	shape.nchildren = children_cson == NULL
	|| is_child ? 0 : cson_size(children_cson);
	scenebuffer_add_shape(scene, &shape, is_child);
	primitive_cson = cson_valueof(cson, CSON_PRIMITIVE_KEY);
	load_primitive(scene, primitive_cson, SHAPEBUFF_TARGET);
	if (children_cson != NULL && is_child == FALSE)
	{
		count = cson_size(children_cson);
		i = 0;
		while (i < count)
			load_shape_data(scene, cson_at(children_cson, i++), TRUE);
	}
}

void		load_shape(t_scene *scene, const t_cson *cson)
{
	return (load_shape_data(scene, cson, FALSE));
}
