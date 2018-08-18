/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_shape.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"

#define TYPE_TIP_MSG	", it should be relation-type string"
#define TYPE_FORMAT_MSG	"Shape's relation type isn't string" TYPE_TIP_MSG
#define TYPE_TYPE_MSG	"Shape's relation type can't be recognized" TYPE_TIP_MSG

static t_err_code	validate_relation_type(const t_cson *cson)
{
	const char *type;

	if (cson == NULL)
		return (RT_NO_ERROR);
	if (cson_is_string(cson) == FALSE)
	{
		return (validation_failed(cson,
		RT_WRONG_VALUE_FORMAT_ERROR, TYPE_FORMAT_MSG));
	}
	type = cson_get_string(cson);
	if (ft_strequ(type, CSON_RELATION_UNION_KEY)
	|| ft_strequ(type, CSON_RELATION_INTERSECTION_KEY)
	|| ft_strequ(type, CSON_RELATION_NEGATION_KEY))
		return (RT_NO_ERROR);
	return (validation_failed(cson, RT_WRONG_VALUE_TYPE_ERROR, TYPE_TYPE_MSG));
}

t_err_code			validate_shape(const t_cson *cson)
{
	t_err_code	err;

	err = validate_relation_type(cson_valueof(cson, CSON_RELATION_KEY));
	err |= validate_primitive(cson);
	return (err);
}
