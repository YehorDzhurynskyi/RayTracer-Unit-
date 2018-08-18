/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repo_vector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepo.h"

t_vec3d		deserialize_vec3d_required(const t_cson *cson, t_bool normalize)
{
	t_vec3d	value;

	value.x = cson_get_real(cson_at(cson, 0));
	value.y = cson_get_real(cson_at(cson, 1));
	value.z = cson_get_real(cson_at(cson, 2));
	if (normalize)
		value = vec3d_normalize(&value);
	return (value);
}

t_vec3d		deserialize_vec3d_optional(const t_cson *cson, t_bool normalize,
const t_vec3d default_value)
{
	if (cson == NULL)
		return (default_value);
	return (deserialize_vec3d_required(cson, normalize));
}

t_clvec3	deserialize_vec3_required(const t_cson *cson, t_bool normalize)
{
	t_vec3d		vec3d;
	t_clvec3	value;

	vec3d = deserialize_vec3d_required(cson, normalize);
	value = (t_clvec3){{vec3d.x, vec3d.y, vec3d.z}};
	return (value);
}

t_clvec3	deserialize_vec3_optional(const t_cson *cson, t_bool normalize,
const t_vec3d default_value)
{
	t_vec3d		vec3d;
	t_clvec3	value;

	vec3d = deserialize_vec3d_optional(cson, normalize, default_value);
	value = (t_clvec3){{vec3d.x, vec3d.y, vec3d.z}};
	return (value);
}

t_cson		*serialize_vec3(const t_clvec3 *vec)
{
	t_cson	*cson;

	cson = cson_array();
	cson_push_real(cson, vec->x);
	cson_push_real(cson, vec->y);
	cson_push_real(cson, vec->z);
	return (cson);
}
