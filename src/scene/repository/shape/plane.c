/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepository.h"

t_plane	deserialize_plane(const t_cson *cson)
{
	t_plane	plane;

	plane.normal = deserialize_vec4(cson_valueof(cson, CSON_NORMAL_KEY), TRUE);
	return (plane);
}

t_cson	*serialize_plane(const t_plane *plane)
{
	t_cson		*cson;
	t_clvec4	normal;

	cson = cson_object();
	normal = plane->normal;
	cson_put(cson, CSON_NORMAL_KEY, serialize_vec4(&normal));
	return (cson);
}
