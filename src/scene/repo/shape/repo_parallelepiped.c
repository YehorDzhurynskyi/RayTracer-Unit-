/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repo_parallelepiped.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepo.h"
#include <math.h>

t_parallelepiped	deserialize_parallelepiped(const t_cson *cson)
{
	t_parallelepiped	parallel;

	parallel.half_width = deserialize_real_required(cson_valueof(cson,
	CSON_WIDTH_KEY)) / 2.0f;
	parallel.half_height = deserialize_real_required(cson_valueof(cson,
	CSON_HEIGHT_KEY)) / 2.0f;
	parallel.half_depth = deserialize_real_required(cson_valueof(cson,
	CSON_DEPTH_KEY)) / 2.0f;
	return (parallel);
}
