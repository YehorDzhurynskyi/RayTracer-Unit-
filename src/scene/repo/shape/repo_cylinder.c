/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repo_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepo.h"
#include <math.h>

t_cylinder	deserialize_cylinder(const t_cson *cson)
{
	t_cylinder		cylinder;

	cylinder.radius2 = deserialize_real_required(cson_valueof(cson, CSON_RADIUS_KEY));
	cylinder.radius2 *= cylinder.radius2;
	return (cylinder);
}

t_cson		*serialize_cylinder(const t_cylinder *cylinder)
{
	t_cson		*cson;

	cson = cson_object();
	cson_put_real(cson, CSON_RADIUS_KEY, sqrt(cylinder->radius2));
	return (cson);
}
