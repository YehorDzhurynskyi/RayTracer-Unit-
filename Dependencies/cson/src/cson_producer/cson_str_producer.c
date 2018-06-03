/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_str_producer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson.h"

char	*cson_produce_str(const t_cson *cson, size_t *size, t_error_code *err)
{
	if (cson == NULL || size == NULL)
	{
		*err = CSON_NULL_PARAMETER_ERROR;
		return (NULL);
	}
	return (NULL);
}
