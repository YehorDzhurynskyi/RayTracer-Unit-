/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repo_dirlightsource.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepo.h"

t_dirlightsource	deserialize_dirlightsource(const t_cson *cson)
{
	t_dirlightsource	dirlightsource;

	dirlightsource.direction = deserialize_vec3_required(cson_valueof(cson,
	CSON_DIRECTION_KEY), TRUE);
	return (dirlightsource);
}
