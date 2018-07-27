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
	if (cson_valueof(cson, CSON_DIFFUSE_COLOR_KEY) != NULL)
		material.diffuse_albedo.color = deserialize_color_required(cson_valueof(cson, CSON_DIFFUSE_COLOR_KEY));
	else
	{
		material.diffuse_albedo.tex_addr = deserialize_int_required(cson_valueof(cson, CSON_DIFFUSE_TEXTURE_KEY));
		material.mask |= DIFFUSE_MASK;
	}
	if (cson_valueof(cson, CSON_SPECULAR_COLOR_KEY) != NULL)
		material.specular_albedo.color = deserialize_color_required(cson_valueof(cson, CSON_SPECULAR_COLOR_KEY));
	else
	{
		material.specular_albedo.tex_addr = deserialize_int_required(cson_valueof(cson, CSON_SPECULAR_TEXTURE_KEY));
		material.mask |= SPECULAR_MASK;
	}
	if (cson_valueof(cson, CSON_GLOSSINESS_KEY) != NULL)
		material.glossiness.value = deserialize_real_required(cson_valueof(cson, CSON_GLOSSINESS_KEY));
	else
	{
		material.glossiness.tex_addr = deserialize_int_required(cson_valueof(cson, CSON_GLOSSINESS_TEXTURE_KEY));
		material.mask |= GLOSSINESS_MASK;
	}
	material.ior = deserialize_real_optional(cson_valueof(cson, CSON_IOR_KEY), IOR);
	material.normal_map = deserialize_int_optional(cson_valueof(cson, CSON_NORMAL_TEXTURE_KEY), NULL_TEXTURE_ADDR);
	if (material.normal_map != NULL_TEXTURE_ADDR)
		material.mask |= NORMAL_MAP_MASK;
	return (material);
}
