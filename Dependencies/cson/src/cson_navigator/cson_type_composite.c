/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_type_composite.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson.h"

inline t_bool	cson_is_array(const t_cson *cson)
{
	return (cson != NULL && cson->value_type == CSON_ARRAY_VALUE_TYPE);
}

inline t_bool	cson_is_object(const t_cson *cson)
{
	return (cson != NULL && cson->value_type == CSON_OBJECT_VALUE_TYPE);
}

inline t_bool	cson_is_composite(const t_cson *cson)
{
	return (cson != NULL && (cson_is_object(cson) || cson_is_array(cson)));
}
