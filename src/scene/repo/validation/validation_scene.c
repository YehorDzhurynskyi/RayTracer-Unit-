/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_scene.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"

#define TIP_MSG		", it should be array of objects"
#define FORMAT_MSG	"Value isn't array" TIP_MSG

#define ITEM_TIP_MSG	", it should be object"
#define ITEM_ABSNET		"Value is absent" ITEM_TIP_MSG
#define ITEM_FORMAT_MSG	"Value isn't object" ITEM_TIP_MSG

static t_err_code	validate_object(const t_cson *cson_item,
t_buff_target target)
{
	t_err_code	err;

	err = RT_NO_ERROR;
	if (cson_item == NULL)
		err |= validation_failed(cson_item,
		RT_VALUE_PARSING_ERROR, ITEM_ABSNET);
	else if (cson_is_object(cson_item) == FALSE)
		err |= validation_failed(cson_item,
		RT_WRONG_VALUE_FORMAT_ERROR, ITEM_FORMAT_MSG);
	if (target == SHAPEBUFF_TARGET)
		err |= validate_shape(cson_item);
	else if (target == LIGHTSOURCEBUFF_TARGET)
		err |= validate_lightsource(cson_item);
	else if (target == MATERIALBUFF_TARGET)
		err |= validate_material(cson_item);
	else if (target == TEXTUREBUFF_TARGET)
		err |= validate_texture(cson_item);
	return (err);
}

static t_err_code	validate_array(const t_cson *arr_cson, t_buff_target target)
{
	t_err_code	err;
	int			count;
	int			i;

	if (arr_cson == NULL)
		return (RT_NO_ERROR);
	if (cson_is_array(arr_cson) == FALSE)
	{
		return (validation_failed(arr_cson,
		RT_WRONG_VALUE_FORMAT_ERROR, FORMAT_MSG));
	}
	err = RT_NO_ERROR;
	count = cson_size(arr_cson);
	i = 0;
	while (i < count)
	{
		err |= validate_object(cson_at(arr_cson, i++), target);
	}
	return (err);
}

t_err_code			validate_scene(const t_cson *cson)
{
	t_err_code	err;

	err = RT_NO_ERROR;
	err |= validate_real_optional_ranged(cson,
	CSON_AMBIENT_KEY, (double[2]){0.0, 1.0}, AMBIENT_STR);
	err |= validate_real_optional_ranged(cson,
	CSON_FOV_KEY, (double[2]){0.0, 180.0}, FOV_STR);
	err |= validate_array(cson_valueof(cson,
	CSON_MATERIALS_KEY), MATERIALBUFF_TARGET);
	err |= validate_array(cson_valueof(cson,
	CSON_LIGHTSOURCES_KEY), LIGHTSOURCEBUFF_TARGET);
	err |= validate_array(cson_valueof(cson,
	CSON_SHAPES_KEY), SHAPEBUFF_TARGET);
	err |= validate_array(cson_valueof(cson,
	CSON_TEXTURES_KEY), TEXTUREBUFF_TARGET);
	err |= validate_camera(cson);
	return (err);
}
