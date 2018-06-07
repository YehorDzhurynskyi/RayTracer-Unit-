/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_get_default_primitive.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson.h"

inline const char	*cson_get_default_string(const t_cson *cson, const char *value)
{
	return (cson_is_string(cson) ? cson->value.string : value);
}

inline long long	cson_get_default_integer(const t_cson *cson, int value)
{
	return (cson_is_integer(cson) ? cson->value.integer : value);
}

inline double		cson_get_default_real(const t_cson *cson, double value)
{
	return (cson_is_real(cson) ? cson->value.real : value);
}

inline t_bool		cson_get_default_boolean(const t_cson *cson, t_bool value)
{
	return (cson_is_boolean(cson) ? cson->value.boolean : value);
}
