/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_sphere.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sceneeditor.h"

t_sphere	scenebuffer_default_sphere(void)
{
	t_sphere	sphere;

	sphere.radius2 = 1.0f;
	return (sphere);
}
