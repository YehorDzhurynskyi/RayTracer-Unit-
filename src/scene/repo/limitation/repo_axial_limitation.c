/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repo_axial_limitation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepo.h"

t_cson				*serialize_axial_limitation(t_cson *actual_limitation_cson,
const t_axial_limitation *axial_limitation)
{
	(void)actual_limitation_cson;
	(void)axial_limitation;
	return (NULL);
}

t_axial_limitation	deserialize_axial_limitation(const t_cson *cson)
{
	t_axial_limitation	axial;

	axial.apply_if_less = deserialize_bool_required(cson_valueof(cson,
	CSON_APPLY_IF_LESS_KEY));
	axial.limit = deserialize_real_required(cson_valueof(cson, CSON_LIMIT_KEY));
	return (axial);
}
