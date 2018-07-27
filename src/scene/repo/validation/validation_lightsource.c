/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_lightsource.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"

#define TYPE_TIP_MSG	", it should be lightsource-type string"
#define TYPE_ABSENT_MSG	"The lightsource type is absent" TYPE_TIP_MSG
#define TYPE_TYPE_MSG	"The lightsource type can't be recognized" TYPE_TIP_MSG
#define TYPE_FORMAT_MSG	"Lightsource type isn't string" TYPE_TIP_MSG

t_err_code	validate_dirlightsource(const t_cson *cson)
{
	return (validate_vec3_required(cson, CSON_DIRECTION_KEY, TRUE));
}

t_err_code	validate_pointlightsource(const t_cson *cson)
{
	t_err_code	err;

	err = validate_vec3_required(cson, CSON_POSITION_KEY, FALSE);
	err |= validate_vec3_optional(cson, CSON_ATTENUATION_KEY, FALSE, "[1 0 0]");
	return (err);
}

t_err_code	validate_spotlightsource(const t_cson *cson)
{
	t_err_code	err;

	err = validate_pointlightsource(cson);
	err |= validate_vec3_required(cson, CSON_DIRECTION_KEY, TRUE);
	err |= validate_real_required(cson, CSON_ANGLE_KEY);
	return (err);
}

static t_err_code	validate_lightsource_type(const t_cson *cson)
{
	const t_cson	*type_cson;
	const char		*type;

	type_cson = cson_valueof(cson, CSON_TYPE_KEY);
	if (type_cson == NULL)
		return (validation_failed(cson, RT_NO_REQUIRED_VALUE_ERROR, TYPE_ABSENT_MSG));
	if (cson_is_string(type_cson) == FALSE)
		return (validation_failed(type_cson, RT_WRONG_VALUE_FORMAT_ERROR, TYPE_FORMAT_MSG));
	type = cson_get_string(type_cson);
	if (ft_strequ(type, CSON_LIGHT_DIRECTIONAL)
	|| ft_strequ(type, CSON_LIGHT_POINT)
	|| ft_strequ(type, CSON_LIGHT_SPOT))
		return (RT_NO_ERROR);
	return (validation_failed(type_cson, RT_WRONG_VALUE_TYPE_ERROR, TYPE_TYPE_MSG));
}

t_err_code	validate_lightsource(const t_cson *cson)
{
	t_err_code	err;
	const char	*type;

	err = validate_lightsource_type(cson);
	err |= validate_primitive(cson);
	err |= validate_color_required(cson, CSON_COLOR_KEY);
	err |= validate_real_required(cson, CSON_INTENSITY_KEY);
	type = cson_get_string(cson_valueof(cson, CSON_TYPE_KEY));
	if (ft_strequ(type, CSON_LIGHT_DIRECTIONAL))
		err |= validate_dirlightsource(cson);
	else if (ft_strequ(type, CSON_LIGHT_POINT))
		err |= validate_pointlightsource(cson);
	else if (ft_strequ(type, CSON_LIGHT_SPOT))
		err |= validate_spotlightsource(cson);
	return (err);
}
