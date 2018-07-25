/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_limitation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"

#define FORMAT_MSG	"Limitations isn't array, it should be an array of limitation objects"

#define TYPE_TIP_MSG	", it should be limitation-type string"
#define TYPE_ABSENT_MSG	"The limitation type is absent" TYPE_TIP_MSG
#define TYPE_TYPE_MSG	"The limitation type can't be recognized" TYPE_TIP_MSG
#define TYPE_FORMAT_MSG	"Limitation type isn't string" TYPE_TIP_MSG

#define ITEM_FORMAT_MSG	"Limitation isn't object, it should be object"

static t_err_code	validate_limitation_type(const t_cson *cson)
{
	const t_cson	*type_cson;
	const char		*type;

	type_cson = cson_valueof(cson, CSON_TYPE_KEY);
	if (type_cson == NULL)
		return (validation_failed(cson, RT_NO_REQUIRED_VALUE_ERROR, TYPE_ABSENT_MSG));
	if (cson_is_string(type_cson) == FALSE)
		return (validation_failed(type_cson, RT_WRONG_VALUE_FORMAT_ERROR, TYPE_FORMAT_MSG));
	type = cson_get_string(type_cson);
	if (ft_strequ(type, CSON_X_AXIS_KEY)
	|| ft_strequ(type, CSON_Y_AXIS_KEY)
	|| ft_strequ(type, CSON_Z_AXIS_KEY))
		return (RT_NO_ERROR);
	return (validation_failed(type_cson, RT_WRONG_VALUE_TYPE_ERROR, TYPE_TYPE_MSG));
}

t_err_code	validate_limitation(const t_cson *cson)
{
	const char	*type;
	t_err_code	err;

	if (cson_is_object(cson) == FALSE)
		return (validation_failed(cson, RT_WRONG_VALUE_FORMAT_ERROR, ITEM_FORMAT_MSG));
	err = validate_limitation_type(cson);
	err |= validate_bool_optional(cson, CSON_IS_RELATIVE_KEY, "TRUE");
	err |= validate_bool_optional(cson, CSON_CUTTING_KEY, "TRUE");
	type = cson_get_string(cson_valueof(cson, CSON_TYPE_KEY));
	if (ft_strequ(type, CSON_X_AXIS_KEY)
	|| ft_strequ(type, CSON_Y_AXIS_KEY)
	|| ft_strequ(type, CSON_Z_AXIS_KEY))
		err |= validate_axial_limitation(cson);
	return (err);
}

t_err_code	validate_axial_limitation(const t_cson *cson)
{
	t_err_code	err;

	err = validate_bool_required(cson, CSON_APPLY_IF_LESS_KEY);
	err |= validate_real_required(cson, CSON_LIMIT_KEY);
	return (err);
}

t_err_code	validate_limitations(const t_cson *cson)
{
	int			count;
	int			i;
	t_err_code	err;

	err = RT_NO_ERROR;
	if (cson == NULL)
		return (RT_NO_ERROR);
	if (cson_is_array(cson) == FALSE)
		return (validation_failed(cson, RT_WRONG_VALUE_FORMAT_ERROR, FORMAT_MSG));
	count = cson_size(cson);
	i = 0;
	while (i < count)
		err |= validate_limitation(cson_at(cson, i++));
	return (err);
}
