/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repo_limitation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepo.h"

t_cson			*serialize_limitation(t_cson *actual_limitation_cson,
const t_limitation *limitation)
{
	(void)actual_limitation_cson;
	(void)limitation;
	return (NULL);
}

static t_limitation_type	recognize_limitation_type(const char *type)
{
	if (ft_strequ(type, CSON_X_AXIS_KEY))
		return (XAXIS);
	else if (ft_strequ(type, CSON_Y_AXIS_KEY))
		return (YAXIS);
	else if (ft_strequ(type, CSON_Z_AXIS_KEY))
		return (ZAXIS);
	return (0);
}

t_limitation	deserialize_limitation(const t_cson *cson)
{
	t_limitation	limitation;

	limitation.is_relative = cson_get_default_boolean(
		cson_valueof(cson, CSON_IS_RELATIVE_KEY), TRUE);
	limitation.cutting = cson_get_default_boolean(
		cson_valueof(cson, CSON_CUTTING_KEY), TRUE);
	limitation.limitation_type = recognize_limitation_type(cson_get_string(
		cson_valueof(cson, CSON_TYPE_KEY)));
	return (limitation);
}
