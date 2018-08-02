/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_choose_material.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 18:07:32 by pzubar            #+#    #+#             */
/*   Updated: 2018/05/29 18:07:35 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "sceneiterator.h"

static const char		*compose_caption(int id)
{
	static char	caption[255];
	size_t		name_len;

	ft_strncpy(caption, "Material, id : ", 255);
	name_len = ft_strlen(caption);
	ft_itoa_cat(caption + name_len, 255 - name_len, id);
	return (caption);
}

static const t_material	*render_material_list(void)
{
	t_iterator			material_iter;
	const t_material	*material;
	const t_material	*selected_material;
	static int			active = -1;
	int					i;

	i = 0;
	selected_material = NULL;
	material_iter = material_begin(&g_main_scene);
	while (has_next(&material_iter))
	{
		material = material_next(&material_iter);
		if (nk_option_label(g_nk_context, compose_caption(i), active == i))
		{
			active = i;
			selected_material = material;
		}
		i++;
	}
	return (selected_material);
}

t_bool					gui_choose_material(const t_material **dest_material)
{
	int				pop_height;
	const t_material	*selected_material;
	t_bool			render_widget;

	render_widget = TRUE;
	gui_popup_start();
	pop_height = g_main_scene.meta.nmaterials * 30 + 75;
	nk_popup_begin(g_nk_context, NK_POPUP_STATIC, "Choose material", 0,
					nk_rect(MATERIAL_CHOOSE_POP_X, MATERIAL_CHOOSE_POP_Y - pop_height, MATERIAL_CHOOSE_POP_WIDTH, pop_height));
	nk_layout_row_dynamic(g_nk_context, 25, 1);
	nk_label(g_nk_context, "Choose material", NK_TEXT_RIGHT);
	selected_material = render_material_list();
	nk_layout_row_dynamic(g_nk_context, 25, 2);
	if (nk_button_label(g_nk_context, "Cancel"))
	{
		*dest_material = NULL;
		render_widget = FALSE;
	}
	if (nk_button_label(g_nk_context, "Change") && selected_material != NULL)
	{
		*dest_material = selected_material;
		render_widget = FALSE;
	}
	nk_popup_end(g_nk_context);
	if (render_widget == FALSE)
		gui_popup_stop();
	return (render_widget);
}
