/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_vector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"

#define TIP_MSG		", it should adhere to [x y z] format"
#define ABSENT_MSG	"Vector is absent" TIP_MSG
#define FORMAT_MSG	"Value isn't vector" TIP_MSG
#define DIMEN_MSG	"Vector has wrong elements count" TIP_MSG
#define NORM_MSG	"Vector has 0 length and couldn't be normalized" TIP_MSG

t_err_code	validate_vec3_required(const t_cson *cson, const char *key, t_bool normalize)
{
	const t_cson	*vec_cson;

	vec_cson = cson_valueof(cson, key);
	if (vec_cson == NULL)
		return (validation_failed(cson, RT_NO_REQUIRED_VALUE_ERROR, ABSENT_MSG));
	return (validate_vec3_optional(cson, key, normalize, ""));
}

t_err_code	validate_vec3_optional(const t_cson *cson, const char *key,
t_bool normalize, const char *default_value_str)
{
	t_vec3d			value;
	const t_cson	*vec_cson;

	vec_cson = cson_valueof(cson, key);
	if (vec_cson == NULL)
		return (validation_set_optional(cson, key, default_value_str));
	if (cson_is_array(vec_cson) == FALSE)
		return (validation_failed(vec_cson, RT_WRONG_VALUE_FORMAT_ERROR, FORMAT_MSG));
	if (cson_size(vec_cson) != 3)
		return (validation_failed(vec_cson, RT_WRONG_DIMENSION_ERROR, DIMEN_MSG));
	if (normalize)
	{
		value.x = cson_get_real(cson_at(vec_cson, 0));
		value.y = cson_get_real(cson_at(vec_cson, 1));
		value.z = cson_get_real(cson_at(vec_cson, 2));
		if (vec3d_length(&value) < 1.0E-6)
			return (validation_failed(vec_cson, RT_ZERO_LENGTH_VECTOR_ERROR, NORM_MSG));
	}
	return (RT_NO_ERROR);
}
