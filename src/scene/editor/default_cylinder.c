/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_cylinder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sceneeditor.h"

t_cylinder	scenebuffer_default_cylinder(void)
{
	t_cylinder	cylinder;

	cylinder.radius2 = 1.0f;
	return (cylinder);
}
