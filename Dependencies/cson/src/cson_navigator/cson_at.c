/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_at.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson.h"

const t_cson	*cson_at(const t_cson *cson, unsigned int index)
{
	t_alst	*array;

	if (cson_is_array(cson) == FALSE)
		return (NULL);
	array = (t_alst*)cson_get_array(cson);
	return (alst_get(array, index));
}
