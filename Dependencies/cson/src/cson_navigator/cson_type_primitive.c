/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_type_primitive.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson.h"

inline t_bool	cson_is_string(const t_cson *cson)
{
	return (cson != NULL && cson->value_type == CSON_STRING_VALUE_TYPE);
}

inline t_bool	cson_is_integer(const t_cson *cson)
{
	return (cson != NULL && cson->value_type == CSON_INTEGER_VALUE_TYPE);
}

inline t_bool	cson_is_real(const t_cson *cson)
{
	return (cson != NULL && cson->value_type == CSON_REAL_VALUE_TYPE);
}

inline t_bool	cson_is_boolean(const t_cson *cson)
{
	return (cson != NULL && cson->value_type == CSON_BOOLEAN_VALUE_TYPE);
}

inline t_bool	cson_is_primitive(const t_cson *cson)
{
	return (cson != NULL && (cson_is_string(cson) || cson_is_integer(cson)
	|| cson_is_real(cson) || cson_is_boolean(cson)));
}
