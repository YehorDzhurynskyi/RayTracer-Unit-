/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_lightsource.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sceneeditor.h"

t_lightsource	scenebuffer_default_lightsource(void)
{
	t_lightsource	lightsource;

	lightsource.color = (t_clcolor){{0xff, 0xff, 0xff, 0.0f}};
	lightsource.intensity = 1.0f;
	return (lightsource);
}
