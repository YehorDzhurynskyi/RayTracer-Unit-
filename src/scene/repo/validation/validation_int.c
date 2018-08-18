/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"

#define TIP_MSG		", it should be integer type value"
#define ABSENT_MSG	"Value is absent" TIP_MSG
#define FORMAT_MSG	"Value isn't integer" TIP_MSG

t_err_code	validate_int_required(const t_cson *cson, const char *key)
{
	const t_cson	*int_cson;

	int_cson = cson_valueof(cson, key);
	if (int_cson == NULL)
	{
		return (validation_failed(cson,
		RT_NO_REQUIRED_VALUE_ERROR, ABSENT_MSG));
	}
	return (validate_int_optional(cson, key, ""));
}

t_err_code	validate_int_optional(const t_cson *cson, const char *key,
const char *default_value_str)
{
	const t_cson	*int_cson;

	int_cson = cson_valueof(cson, key);
	if (int_cson == NULL)
		return (validation_set_optional(cson, key, default_value_str));
	if (cson_is_integer(int_cson) == FALSE)
	{
		return (validation_failed(int_cson,
		RT_WRONG_VALUE_FORMAT_ERROR, FORMAT_MSG));
	}
	return (RT_NO_ERROR);
}
