/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spotlightsource.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepository.h"
#include <math.h>
#include "logger.h"

#define SPOT_ANGLE		20.0
#define SPOT_ANGLE_STR	TO_STRING(SPOT_ANGLE)

t_spotlightsource	deserialize_spotlightsource(const t_cson *cson, t_err_code *err)
{
	t_spotlightsource		spotlightsource;

	spotlightsource.position = deserialize_vec3(cson, CSON_POSITION_KEY,
	RT_VEC_REPO_REQUIRED, err);
	spotlightsource.direction = deserialize_vec3(cson, CSON_DIRECTION_KEY,
	RT_VEC_REPO_REQUIRED | RT_VEC_REPO_NORMALIZE, err);
	spotlightsource.attenuation = deserialize_vec3(cson,
	CSON_ATTENUATION_KEY, 0, err);
	if (*err == RT_NO_OPTIONAL_VALUE_ERROR)
	{
		log_notify("'attenuation' value is set to [1, 0, 0] by default");
		spotlightsource.attenuation = (t_clvec3){{1.0f, 0.0f, 0.0f}};
		*err = RT_NO_ERROR;
	}
	spotlightsource.cosangle = deserialize_real(cson, CSON_ANGLE_KEY, SPOT_ANGLE, SPOT_ANGLE_STR);
	spotlightsource.cosangle = cos(spotlightsource.cosangle * M_PI / 180.0);
	return (spotlightsource);
}

t_cson		*serialize_spotlightsource(const t_spotlightsource *spotlightsource)
{
	t_cson		*cson;
	t_clvec3	direction;
	t_clvec3	position;
	t_clvec3	attenuation;

	cson = cson_object();
	direction = spotlightsource->direction;
	position = spotlightsource->position;
	attenuation = spotlightsource->attenuation;
	cson_put(cson, CSON_DIRECTION_KEY, serialize_vec3(&direction));
	cson_put(cson, CSON_POSITION_KEY, serialize_vec3(&position));
	cson_put(cson, CSON_ATTENUATION_KEY, serialize_vec3(&attenuation));
	cson_put_real(cson, CSON_ANGLE_KEY, (180.0 / M_PI)
	* acos(spotlightsource->cosangle));
	return (cson);
}
