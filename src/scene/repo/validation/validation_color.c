/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"

#define TIP_MSG		", it should adhere to ARGB8 in hex string format"
#define ABSENT_MSG	"Color is absent" TIP_MSG
#define FORMAT_MSG	"Color isn't string" TIP_MSG
#define SYMBOL_MSG	"Invalid symbol in color string" TIP_MSG
#define DIMEN_NSG	"Invalid dimension of hex value color" TIP_MSG

static t_err_code	validate_color_str(const t_cson *color_cson)
{
	unsigned int	count;
	const char		*colorstr;

	colorstr = cson_get_string(color_cson);
	if (colorstr[0] == '0' && (colorstr[1] == 'x' || colorstr[1] == 'X'))
		colorstr += 2;
	count = 0;
	while (*colorstr)
	{
		if (ft_ishex(*colorstr++) == FALSE)
		{
			return (validation_failed(color_cson,
			RT_WRONG_VALUE_FORMAT_ERROR, SYMBOL_MSG));
		}
		++count;
	}
	if (count != 8)
	{
		return (validation_failed(color_cson,
		RT_WRONG_DIMENSION_ERROR, DIMEN_NSG));
	}
	return (RT_NO_ERROR);
}

t_err_code			validate_color_required(const t_cson *cson, const char *key)
{
	const t_cson	*color_cson;

	color_cson = cson_valueof(cson, key);
	if (color_cson == NULL)
	{
		return (validation_failed_parent(cson, key,
		RT_NO_REQUIRED_VALUE_ERROR, ABSENT_MSG));
	}
	return (validate_color_optional(cson, key, ""));
}

t_err_code			validate_color_optional(const t_cson *cson,
const char *key, const char *default_value_str)
{
	const t_cson	*color_cson;

	color_cson = cson_valueof(cson, key);
	if (color_cson == NULL)
		return (validation_set_optional(cson, key, default_value_str));
	if (cson_is_string(color_cson) == FALSE)
	{
		return (validation_failed(color_cson,
		RT_WRONG_VALUE_FORMAT_ERROR, FORMAT_MSG));
	}
	return (validate_color_str(color_cson));
}
