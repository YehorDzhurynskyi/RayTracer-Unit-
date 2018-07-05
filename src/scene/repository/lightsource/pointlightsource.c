/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointlightsource.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepository.h"
#include "logger.h"

t_pointlightsource	deserialize_pointlightsource(const t_cson *cson, t_err_code *err)
{
	t_pointlightsource	pointlightsource;

	pointlightsource.position = deserialize_vec3(cson, CSON_POSITION_KEY,
	RT_VEC_REPO_REQUIRED, err);
	pointlightsource.attenuation = deserialize_vec3(cson,
	CSON_ATTENUATION_KEY, 0, err);
	if (*err == RT_NO_OPTIONAL_VALUE_ERROR)
	{
		log_notify("'" CSON_ATTENUATION_KEY "' value is set to [1, 0, 0] by default");
		pointlightsource.attenuation = (t_clvec3){{1.0f, 0.0f, 0.0f}};
		*err = RT_NO_ERROR;
	}
	return (pointlightsource);
}

t_cson			*serialize_pointlight(const t_pointlightsource *pointlightsource)
{
	t_cson		*cson;
	t_clvec3	position;
	t_clvec3	attenuation;

	cson = cson_object();
	position = pointlightsource->position;
	attenuation = pointlightsource->attenuation;
	cson_put(cson, CSON_POSITION_KEY, serialize_vec3(&position));
	cson_put(cson, CSON_ATTENUATION_KEY, serialize_vec3(&attenuation));
	return (cson);
}
