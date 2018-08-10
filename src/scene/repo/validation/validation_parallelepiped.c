/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_parallelepiped.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"

t_err_code	validate_parallelepiped(const t_cson *cson)
{
	t_err_code	err;

	err = validate_real_required_ranged(cson, CSON_WIDTH_KEY, (double[2]){0.0, INFINITY});
	err |= validate_real_required_ranged(cson, CSON_HEIGHT_KEY, (double[2]){0.0, INFINITY});
	err |= validate_real_required_ranged(cson, CSON_DEPTH_KEY, (double[2]){0.0, INFINITY});
	return (err);
}
