/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repo_torus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepo.h"
#include <math.h>

t_torus	deserialize_torus(const t_cson *cson)
{
	t_torus	torus;

	torus.near_radius = deserialize_real_required(cson_valueof(cson,
	CSON_NEAR_RADIUS_KEY));
	torus.far_radius = deserialize_real_required(cson_valueof(cson,
	CSON_FAR_RADIUS_KEY));
	return (torus);
}
