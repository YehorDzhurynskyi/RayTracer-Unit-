/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repo_pointlightsource.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepo.h"

t_pointlightsource	deserialize_pointlightsource(const t_cson *cson)
{
	t_pointlightsource	pointlightsource;

	pointlightsource.attenuation = deserialize_vec3_optional(cson_valueof(cson,
	CSON_ATTENUATION_KEY), FALSE,
	(t_vec3d){1.0, 0.0, 0.0});
	return (pointlightsource);
}
