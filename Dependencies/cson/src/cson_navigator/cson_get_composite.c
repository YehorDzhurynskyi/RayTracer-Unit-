/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_get_composite.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson.h"

inline const t_alst	*cson_get_array(const t_cson *cson)
{
	return (cson_is_array(cson) ? cson->value.tuple : NULL);
}

inline const t_alst	*cson_get_object(const t_cson *cson)
{
	return (cson_is_object(cson) ? cson->value.tuple : NULL);
}
