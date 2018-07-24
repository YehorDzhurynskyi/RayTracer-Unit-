/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repo_material.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepo.h"

t_material	deserialize_material(const t_cson *cson)
{
	t_material	material;

	material.mask = 0;
	material.diffuse_albedo.color = deserialize_color_required(cson_valueof(cson, CSON_DIFFUSE_COLOR_KEY));
	material.specular_albedo.color = deserialize_color_required(cson_valueof(cson, CSON_SPECULAR_COLOR_KEY));
	material.glossiness.value = deserialize_real_optional(cson_valueof(cson, CSON_GLOSSINESS_KEY), GLOSSINESS);
	material.ior = deserialize_real_optional(cson_valueof(cson, CSON_IOR_KEY), IOR);
	material.normal_map = NULL_RESOURCE_ID;
	return (material);
}
