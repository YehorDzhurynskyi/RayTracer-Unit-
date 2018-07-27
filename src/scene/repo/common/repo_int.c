/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repo_int.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepo.h"

cl_int	deserialize_int_required(const t_cson *cson)
{
	return (cson_get_integer(cson));
}

cl_int	deserialize_int_optional(const t_cson *cson, const cl_int default_value)
{
	if (cson == NULL)
		return (default_value);
	return (deserialize_int_required(cson));
}
