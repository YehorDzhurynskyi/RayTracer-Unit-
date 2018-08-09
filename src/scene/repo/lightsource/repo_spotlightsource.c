/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repo_spotlightsource.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepo.h"
#include <math.h>

t_spotlightsource	deserialize_spotlightsource(const t_cson *cson)
{
	t_spotlightsource		spotlightsource;

	spotlightsource.direction = deserialize_vec3_required(cson_valueof(cson, CSON_DIRECTION_KEY), TRUE);
	spotlightsource.attenuation = deserialize_vec3_optional(cson_valueof(cson, CSON_ATTENUATION_KEY), FALSE,
	(t_vec3d){1.0, 0.0, 0.0});
	spotlightsource.cosangle = deserialize_real_required(cson_valueof(cson, CSON_ANGLE_KEY));
	spotlightsource.cosangle = cos(spotlightsource.cosangle * M_PI / 180.0);
	return (spotlightsource);
}
