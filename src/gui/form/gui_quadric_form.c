/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_quadric_form.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 13:59:40 by pzubar            #+#    #+#             */
/*   Updated: 2018/07/05 13:59:42 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui_object_form.h"
#include "sceneeditor.h"

#define PREFIX				nk_property_float(g_nk_context,
#define PROPERTY(LBL, ADDR)	PREFIX LBL, -INFINITY, ADDR, INFINITY, 1.0f, 1.0f)

// static void	update_quadric(const t_shape *shape, const t_quadric_surface *old_quadric_surface,
// const t_quadric_surface *new_quadric_surface)
// {
// 	t_bool	up_to_date;

// 	up_to_date = ft_memcmp(old_quadric_surface, new_quadric_surface, sizeof(t_quadric_surface)) == 0;
// 	if (up_to_date)
// 		return ;
// 	scenebuffer_map(&g_main_scene, shape->addr + sizeof(t_shape) + sizeof(t_primitive),
// 	sizeof(t_quadric_surface), SHAPEBUFF_TARGET);
// 	scenebuffer_put(&g_main_scene, (void*)new_quadric_surface, 0, sizeof(t_quadric_surface));
// 	scenebuffer_unmap(&g_main_scene, SHAPEBUFF_TARGET);
// }

void		render_quadric_form(const t_shape *shape, const t_quadric_surface *quadric)
{
	t_quadric_surface	new_quadric;
	// float				coefs[10];

	(void)shape;
	// TODO: finish
	if (nk_tree_push(g_nk_context, NK_TREE_TAB, "Quadric", NK_MAXIMIZED))
	{
		new_quadric = *quadric;
		nk_layout_row_dynamic(g_nk_context, 30, 1);
		nk_label_colored(g_nk_context, "Coefficients", NK_TEXT_LEFT, property_color);
		// PROPERTY("#xx", &coefs[0]);
		// PROPERTY("#yy", &coefs[1]);
		// PROPERTY("#zz", &coefs[2]);
		// PROPERTY("#2xy", &coefs[3]);
		// PROPERTY("#2yz", &coefs[4]);
		// PROPERTY("#2xz", &coefs[5]);
		// PROPERTY("#2x", &coefs[6]);
		// PROPERTY("#2y", &coefs[7]);
		// PROPERTY("#2z", &coefs[8]);
		// PROPERTY("#C", &coefs[9]);
		// update_quadric(shape, quadric, &new_quadric);
		nk_tree_pop(g_nk_context);
	}
}
