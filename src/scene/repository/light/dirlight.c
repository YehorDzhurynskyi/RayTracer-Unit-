/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirlight.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepository.h"

t_dirlight	deserialize_dirlight(const t_cson *cson, t_err_code *err)
{
	t_dirlight		dirlight;
	const t_cson	*direction_cson;

	direction_cson = cson_valueof(cson, CSON_DIRECTION_KEY);
	if (direction_cson == NULL)
	{
		*err = RT_NO_REQUIRED_VALUE_ERROR;
		log_error("Direction light's diretion vector is absent", *err);
		return ((t_dirlight){});
	}
	dirlight.direction = deserialize_vec4(direction_cson, TRUE, err);
	return (dirlight);
}

t_cson		*serialize_dirlight(const t_dirlight *dirlight)
{
	t_cson		*cson;
	t_clvec4	direction;

	cson = cson_object();
	direction = dirlight->direction;
	cson_put(cson, CSON_DIRECTION_KEY, serialize_vec4(&direction));
	return (cson);
}
