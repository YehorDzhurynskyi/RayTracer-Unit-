/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repo_shape.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepo.h"
#include "sceneeditor.h"

static t_relation_type	recognize_relation_type(const t_cson *cson)
{
	const char	*type;

	type = cson_get_string(cson);
	if (ft_strequ(type, CSON_RELATION_INTERSECTION_KEY))
		return (INTERSECTION);
	else if (ft_strequ(type, CSON_RELATION_NEGATION_KEY))
		return (NEGATION);
	return (UNION);
}

t_shape					deserialize_shape(const t_cson *cson)
{
	t_shape	shape;

	shape.relation_type = recognize_relation_type(cson_valueof(cson,
	CSON_RELATION_KEY));
	shape.nchildren = 0;
	shape.material_addr = deserialize_int_optional(cson_valueof(cson,
	CSON_MATERIAL_KEY), DEFAULT_MATERIAL_ID);
	return (shape);
}
