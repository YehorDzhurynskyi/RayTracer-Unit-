/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_form_utilities.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 13:59:40 by pzubar            #+#    #+#             */
/*   Updated: 2018/07/05 13:59:42 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui_object_form.h"

struct nk_color	property_color = (struct nk_color){168, 80, 19, 255};

struct nk_color	to_nkcolor(t_clcolor color)
{
	return ((struct nk_color){color.x, color.y, color.z, 255 - color.w});
}

t_clcolor		from_nkcolor(struct nk_color color)
{
	return ((t_clcolor){{color.r, color.g, color.b, 255 - color.a}});
}
