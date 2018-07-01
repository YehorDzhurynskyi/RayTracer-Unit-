/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirlightsource.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepository.h"

t_dirlightsource	deserialize_dirlightsource(const t_cson *cson, t_err_code *err)
{
	t_dirlightsource	dirlightsource;

	dirlightsource.direction = deserialize_vec3(cson, CSON_DIRECTION_KEY,
	RT_VEC_REPO_REQUIRED | RT_VEC_REPO_NORMALIZE, err);
	return (dirlightsource);
}

t_cson				*serialize_dirlightsource(const t_dirlightsource *dirlightsource)
{
	t_cson		*cson;
	t_clvec3	direction;

	cson = cson_object();
	direction = dirlightsource->direction;
	cson_put(cson, CSON_DIRECTION_KEY, serialize_vec3(&direction));
	return (cson);
}
