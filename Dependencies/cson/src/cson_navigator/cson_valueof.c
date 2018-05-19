/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_valueof.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson.h"

const t_cson	*cson_valueof(const t_cson *cson, const char *key)
{
	t_alst			*object;
	unsigned int	i;
	t_cson			*needle;

	if (cson_is_object(cson) == FALSE)
		return (NULL);
	object = (t_alst*)cson_get_object(cson);
	i = 0;
	while (i < object->size)
	{
		needle = (t_cson*)alst_get(object, i++);
		if (ft_strequ(needle->key, key))
			return (needle);
	}
	return (NULL);
}
