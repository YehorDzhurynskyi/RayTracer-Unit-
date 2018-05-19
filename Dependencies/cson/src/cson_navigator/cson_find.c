/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_find.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson.h"

const t_cson			*cson_find(const t_cson *cson, char *nodepath)
{
	char	*delim;

	if (*nodepath == '\0')
		return (cson);
	if (*nodepath == '/')
		cson = cson_root(cson);
	delim = ft_strchr(nodepath, '/');
	if (delim == NULL)
		return (cson_valueof(cson, nodepath));
	*delim++ = '\0';
	if (ft_strequ(nodepath, ".."))
		return (cson_find(cson->parent, delim));
	else if (ft_strequ(nodepath, "."))
		return (cson_find(cson, delim));
	else if (cson_is_array(cson))
		return (cson_find(cson_at(cson, ft_atoi(nodepath)), delim));
	return (cson_find(cson_valueof(cson, nodepath), delim));
}
