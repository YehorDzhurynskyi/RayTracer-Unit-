/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_cone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sceneeditor.h"

t_cone	scenebuffer_default_cone(void)
{
	t_cone	cone;

	cone.cos2angle = cos(15.0 * M_PI / 180.0);
	cone.cos2angle *= cone.cos2angle;
	return (cone);
}
