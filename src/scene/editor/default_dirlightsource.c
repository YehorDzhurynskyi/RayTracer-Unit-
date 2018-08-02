/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_dirlightsource.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sceneeditor.h"

t_dirlightsource	scenebuffer_default_dirlightsource(void)
{
	t_dirlightsource	dirlightsource;

	dirlightsource.direction = (t_clvec4){{0.0f, -1.0f, 0.0f, 0.0f}};
	return (dirlightsource);
}
