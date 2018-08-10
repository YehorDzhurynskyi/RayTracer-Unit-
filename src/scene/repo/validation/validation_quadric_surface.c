/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_quadric_surface.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"

#define TIP_MSG		", it should adhere to [a b c d e ...] format with 10 elements"
#define ABSENT_MSG	"Coefficient vector is absent" TIP_MSG
#define FORMAT_MSG	"Value isn't vector" TIP_MSG
#define DIMEN_MSG	"Vector has wrong elements count" TIP_MSG

t_err_code	validate_quadric_surface(const t_cson *cson)
{
	const t_cson	*vec_cson;

	vec_cson = cson_valueof(cson, CSON_COEFS_KEY);
	if (vec_cson == NULL)
		return (validation_failed_parent(cson, CSON_COEFS_KEY, RT_NO_REQUIRED_VALUE_ERROR, ABSENT_MSG));
	if (cson_is_array(vec_cson) == FALSE)
		return (validation_failed(vec_cson, RT_WRONG_VALUE_FORMAT_ERROR, FORMAT_MSG));
	if (cson_size(vec_cson) != 10)
		return (validation_failed(vec_cson, RT_WRONG_DIMENSION_ERROR, DIMEN_MSG));
	return (RT_NO_ERROR);
}
