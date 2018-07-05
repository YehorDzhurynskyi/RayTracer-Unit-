/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepository.h"

#define GLOSSINESS			0.0
#define GLOSSINESS_STR		TO_STRING(GLOSSINESS)
#define IOR					1.0
#define IOR_STR				TO_STRING(IOR)

t_material	deserialize_material(const t_cson *cson, t_err_code *err)
{
	t_material	material;

	material.mask = 0;
	material.diffuse_albedo.color = deserialize_color(cson, CSON_DIFFUSE_COLOR_KEY, err);
	material.specular_albedo.color = deserialize_color(cson, CSON_SPECULAR_COLOR_KEY, err);
	material.glossiness.value = deserialize_real(cson, CSON_GLOSSINESS_KEY,
	GLOSSINESS, GLOSSINESS_STR);
	material.ior = deserialize_real(cson, CSON_IOR_KEY,
	IOR, IOR_STR);
	material.normal_map = NULL_RESOURCE_ID;

	return (material);
}
