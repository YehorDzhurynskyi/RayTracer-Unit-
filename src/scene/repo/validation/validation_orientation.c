/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_orientation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"

#define TIP_MSG		", it should adhere to 3d-vector format"
#define ABSENT_MSG	"Orientation vector is absent" TIP_MSG
#define FORMAT_MSG	"Orientation vector isn't array" TIP_MSG
#define DIMEN_MSG	"Invalid dimension of orientation vector" TIP_MSG

t_err_code	validate_orientation_required(const t_cson *cson, const char *key)
{
	const t_cson	*orientation_cson;

	orientation_cson = cson_valueof(cson, key);
	if (orientation_cson == NULL)
		return (validation_failed(cson, RT_NO_REQUIRED_VALUE_ERROR, ABSENT_MSG));
	return (validate_orientation_optional(cson, key, ""));
}

t_err_code	validate_orientation_optional(const t_cson *cson, const char *key, const char *default_angles_str)
{
	const t_cson	*orientation_cson;

	orientation_cson = cson_valueof(cson, key);
	if (orientation_cson == NULL)
		return (validation_set_optional(cson, key, default_angles_str));
	if (cson_is_array(orientation_cson) == FALSE)
		return (validation_failed(orientation_cson, RT_WRONG_VALUE_FORMAT_ERROR, FORMAT_MSG));
	if (cson_size(orientation_cson) != 3)
		return (validation_failed(orientation_cson, RT_WRONG_DIMENSION_ERROR, DIMEN_MSG));
	return (RT_NO_ERROR);
}
