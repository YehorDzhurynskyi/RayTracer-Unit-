/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repo_bool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scenerepo.h"

t_clbool	deserialize_bool_required(const t_cson *cson)
{
	return (cson_get_boolean(cson));
}

t_clbool	deserialize_bool_optional(const t_cson *cson,
const t_clbool default_value)
{
	if (cson == NULL)
		return (default_value);
	return (deserialize_bool_required(cson));
}
