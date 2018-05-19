/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_get_primitive.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson.h"

inline const char	*cson_get_string(const t_cson *cson)
{
	return (cson_is_string(cson) ? cson->value.string : NULL);
}

inline long long	cson_get_integer(const t_cson *cson)
{
	return (cson_is_integer(cson) ? cson->value.integer : 0);
}

inline double		cson_get_real(const t_cson *cson)
{
	return (cson_is_real(cson) ? cson->value.real : 0.0);
}

inline t_bool		cson_get_boolean(const t_cson *cson)
{
	return (cson_is_boolean(cson) ? cson->value.boolean : FALSE);
}
