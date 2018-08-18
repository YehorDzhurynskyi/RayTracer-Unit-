/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_choose_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 18:07:32 by pzubar            #+#    #+#             */
/*   Updated: 2018/05/29 18:07:35 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "sceneiterator.h"

static const char		*compose_caption(const t_texture *texture, int id)
{
	static char				caption[255];
	const t_climage_texture	*resource_texture;
	size_t					name_len;

	if (texture->texture_type == CLIMAGE)
	{
		resource_texture = (const t_climage_texture*)(texture + 1);
		ft_strncpy(caption, texture_map_at(&g_main_scene.texture_map,
			resource_texture->tex_index), 255);
		ft_strlcat(caption, ", id : ", 255);
	}
	else
	{
		ft_strncpy(caption, g_texture_captions[texture->texture_type - 1], 255);
		ft_strlcat(caption, " texture, id : ", 255);
	}
	name_len = ft_strlen(caption);
	ft_itoa_cat(caption + name_len, 255 - name_len, id);
	return (caption);
}

static const t_texture	*render_texture_list(void)
{
	t_iterator		texture_iter;
	const t_texture	*texture;
	const t_texture	*selected_texture;
	static int		active = -1;
	int				i;

	i = 0;
	selected_texture = NULL;
	texture_iter = texture_begin(&g_main_scene);
	while (has_next(&texture_iter))
	{
		texture = texture_next(&texture_iter);
		if (nk_option_label(g_nk_context,
				compose_caption(texture, i), active == i))
		{
			active = i;
			selected_texture = texture;
		}
		i++;
	}
	return (selected_texture);
}

static t_bool			return_texture(const t_texture **dest_texture,
const t_texture *selected_texture)
{
	t_bool	render_widget;

	render_widget = TRUE;
	if (nk_button_label(g_nk_context, "Cancel"))
	{
		*dest_texture = NULL;
		render_widget = FALSE;
	}
	if (nk_button_label(g_nk_context, "Change") && selected_texture != NULL)
	{
		*dest_texture = selected_texture;
		render_widget = FALSE;
	}
	return (render_widget);
}

t_bool					gui_choose_texture(const t_texture **dest_texture)
{
	int				pop_height;
	const t_texture	*selected_texture;
	t_bool			render_widget;

	render_widget = TRUE;
	gui_popup_start();
	pop_height = g_main_scene.meta.ntextures * 30 + 75;
	nk_popup_begin(g_nk_context, NK_POPUP_STATIC, "Choose texture", 0,
		nk_rect(TEXTURE_CHOOSE_POP_X, TEXTURE_CHOOSE_POP_Y - pop_height,
		TEXTURE_CHOOSE_POP_WIDTH, pop_height));
	nk_layout_row_dynamic(g_nk_context, 25, 1);
	nk_label(g_nk_context, "Choose texture", NK_TEXT_RIGHT);
	selected_texture = render_texture_list();
	nk_layout_row_dynamic(g_nk_context, 25, 2);
	render_widget = return_texture(dest_texture, selected_texture);
	nk_popup_end(g_nk_context);
	if (render_widget == FALSE)
		gui_popup_stop();
	return (render_widget);
}
