/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_real.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"
#include <limits.h>

#define TIP_MSG		", it should be real type value"
#define ABSENT_MSG	"Value is absent" TIP_MSG
#define FORMAT_MSG	"Value isn't real" TIP_MSG
#define RANGE_MSG	"Value doesn't fit in range" TIP_MSG

t_err_code	validate_real_required(const t_cson *cson, const char *key)
{
	return (validate_real_required_ranged(cson, key, (double[2]){DBL_MIN, DBL_MAX}));
}

t_err_code	validate_real_optional(const t_cson *cson, const char *key, const char *default_value_str)
{
	return (validate_real_optional_ranged(cson, key, (double[2]){DBL_MIN, DBL_MAX}, default_value_str));
}

t_err_code	validate_real_required_ranged(const t_cson *cson, const char *key, const double range[2])
{
	const t_cson	*real_cson;

	real_cson = cson_valueof(cson, key);
	if (real_cson == NULL)
		return (validation_failed(cson, RT_NO_REQUIRED_VALUE_ERROR, ABSENT_MSG));
	return (validate_real_optional_ranged(cson, key, range, ""));
}

t_err_code	validate_real_optional_ranged(const t_cson *cson, const char *key, const double range[2], const char *default_value_str)
{
	const t_cson	*real_cson;
	double			value;

	real_cson = cson_valueof(cson, key);
	if (real_cson == NULL)
		return (validation_set_optional(cson, key, default_value_str));
	if (cson_is_real(real_cson) == FALSE)
		return (validation_failed(real_cson, RT_WRONG_VALUE_FORMAT_ERROR, FORMAT_MSG));
	value = cson_get_real(real_cson);
	if (value < range[0] || value > range[1])
		return (validation_failed(real_cson, RT_WRONG_VALUE_RANGE_ERROR, RANGE_MSG));
	return (RT_NO_ERROR);
}
