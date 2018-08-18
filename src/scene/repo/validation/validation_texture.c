/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"

#define TYPE_TIP_MSG	", it should be texture-type string"
#define TYPE_ABSENT_MSG	"The texture type is absent" TYPE_TIP_MSG
#define TYPE_TYPE_MSG	"The texture type can't be recognized" TYPE_TIP_MSG
#define TYPE_FORMAT_MSG	"Texture type isn't string" TYPE_TIP_MSG

static t_err_code	validate_texture_type(const t_cson *cson)
{
	const t_cson	*type_cson;
	const char		*type;

	type_cson = cson_valueof(cson, CSON_TYPE_KEY);
	if (type_cson == NULL)
	{
		return (validation_failed(cson,
		RT_NO_REQUIRED_VALUE_ERROR, TYPE_ABSENT_MSG));
	}
	if (cson_is_string(type_cson) == FALSE)
	{
		return (validation_failed(type_cson,
		RT_WRONG_VALUE_FORMAT_ERROR, TYPE_FORMAT_MSG));
	}
	type = cson_get_string(type_cson);
	if (ft_strequ(type, CSON_TEXTURE_CHESS)
	|| ft_strequ(type, CSON_TEXTURE_RESOURCE)
	|| ft_strequ(type, CSON_TEXTURE_WAVE)
	|| ft_strequ(type, CSON_TEXTURE_PERLIN_NOISE))
		return (RT_NO_ERROR);
	return (validation_failed(type_cson,
	RT_WRONG_VALUE_TYPE_ERROR, TYPE_TYPE_MSG));
}

t_err_code			validate_texture(const t_cson *cson)
{
	t_err_code	err;
	const char	*type;

	err = validate_texture_type(cson);
	err |= validate_real_optional_ranged(cson,
	CSON_SCALE_KEY, (double[2]){1.0, 20.0}, SCALE_STR);
	err |= validate_real_optional(cson, CSON_UOFFSET_KEY, UOFFSET_STR);
	err |= validate_real_optional(cson, CSON_VOFFSET_KEY, VOFFSET_STR);
	type = cson_get_string(cson_valueof(cson, CSON_TYPE_KEY));
	if (ft_strequ(type, CSON_TEXTURE_CHESS))
		err |= validate_chess_texture(cson);
	else if (ft_strequ(type, CSON_TEXTURE_RESOURCE))
		err |= validate_climage_texture(cson);
	return (err);
}
