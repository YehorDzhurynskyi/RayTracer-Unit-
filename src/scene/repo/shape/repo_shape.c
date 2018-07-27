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

t_shape	deserialize_shape(const t_cson *cson)
{
	t_shape	shape;

	shape.relation_type = recognize_relation_type(cson_valueof(cson, CSON_RELATION_KEY));
	shape.nchildren = 0;
	shape.material_addr = deserialize_int_optional(cson_valueof(cson, CSON_MATERIAL_KEY), DEFAULT_MATERIAL_ID);
	return (shape);
}

static const char	*relation_type_str(t_relation_type type)
{
	if (type == UNION)
		return ("union");
	else if (type == INTERSECTION)
		return ("intersection");
	else if (type == NEGATION)
		return ("negation");
	return ("unrecognized relation type");
}

t_cson				*serialize_shape(const t_shape *shape)
{
	t_cson	*cson;

	cson = cson_object();
	cson_put_string(cson, CSON_RELATION_KEY, relation_type_str(shape->relation_type));
	return (cson);
}
