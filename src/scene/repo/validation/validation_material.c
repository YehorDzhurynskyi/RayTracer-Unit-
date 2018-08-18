/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_material.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"

#define TIP			" property, which are mutually exclusive"
#define PRE			"Material should have "
#define DIFFUSE_MSG	PRE "'diffuse_color' or 'diffuse_texture'" TIP
#define SPEC_MSG	PRE "'specular_color' or 'specular_texture'" TIP
#define GLOSS_MSG	PRE "'glossiness' or 'glossiness_texture'" TIP

static t_err_code	validate_material_glossiness(const t_cson *cson)
{
	const t_cson	*real_cson;
	const t_cson	*tex_cson;

	real_cson = cson_valueof(cson, CSON_GLOSSINESS_KEY);
	tex_cson = cson_valueof(cson, CSON_GLOSSINESS_TEXTURE_KEY);
	if ((real_cson == NULL && tex_cson == NULL)
	|| (real_cson != NULL && tex_cson != NULL))
	{
		return (validation_failed(cson,
		RT_NO_REQUIRED_VALUE_ERROR, GLOSS_MSG));
	}
	if (real_cson != NULL)
	{
		return (validate_real_required_ranged(cson,
		CSON_GLOSSINESS_KEY, (double[2]){0.0, 1.0}));
	}
	else if (tex_cson != NULL)
		return (validate_int_required(cson, CSON_GLOSSINESS_TEXTURE_KEY));
	return (RT_NO_ERROR);
}

static t_err_code	validate_material_color(const t_cson *cson,
const char *color_key, const char *tex_key, const char *message)
{
	const t_cson	*color_cson;
	const t_cson	*tex_cson;

	color_cson = cson_valueof(cson, color_key);
	tex_cson = cson_valueof(cson, tex_key);
	if ((color_cson == NULL && tex_cson == NULL)
	|| (color_cson != NULL && tex_cson != NULL))
		return (validation_failed(cson, RT_NO_REQUIRED_VALUE_ERROR, message));
	if (color_cson != NULL)
		return (validate_color_required(cson, color_key));
	else if (tex_cson != NULL)
		return (validate_int_required(cson, tex_key));
	return (RT_NO_ERROR);
}

t_err_code			validate_material(const t_cson *cson)
{
	t_err_code	err;

	err = validate_material_color(cson, CSON_DIFFUSE_COLOR_KEY,
	CSON_DIFFUSE_TEXTURE_KEY, DIFFUSE_MSG);
	err |= validate_material_color(cson, CSON_SPECULAR_COLOR_KEY,
	CSON_SPECULAR_TEXTURE_KEY, SPEC_MSG);
	err |= validate_material_glossiness(cson);
	err |= validate_real_optional_ranged(cson, CSON_IOR_KEY,
	(double[2]){0.0, 2.0}, IOR_STR);
	return (err);
}
