/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_limitations_form.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 13:59:40 by pzubar            #+#    #+#             */
/*   Updated: 2018/07/05 13:59:42 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui_object_form.h"
#include "sceneeditor.h"

static const char	*g_limitation_captions[] = {
	"X-Axis",
	"Y-Axis",
	"Z-Axis"
};

static void	render_limitation_item(const t_limitation *limitation, int tree_item_id)
{
	char	caption[255];
	size_t	name_len;

	ft_strncpy(caption, g_limitation_captions[limitation->limitation_type - 1], 255);
	ft_strlcat(caption, ", id : ", 255);
	name_len = ft_strlen(caption);
	ft_itoa_cat(caption + name_len, 255 - name_len, tree_item_id);
	if (nk_tree_push_id(g_nk_context, NK_TREE_NODE,
		caption, NK_MINIMIZED, tree_item_id))
	{
		if (nk_button_label(g_nk_context, "Select"))
		{
			// TODO: select limit
		}
		nk_tree_pop(g_nk_context);
	}
}

void		render_limitations(const t_shape *shape, const t_primitive *primitive)
{
	t_iterator			limitation_iter;
	const t_limitation	*limitation;
	int					i;

	(void)shape;
	if (nk_tree_push(g_nk_context, NK_TREE_TAB, "Limitations", NK_MAXIMIZED))
	{
		if (nk_button_symbol_label(g_nk_context, NK_SYMBOL_PLUS, "Add limitation", NK_TEXT_ALIGN_RIGHT))
		{
			// TODO: add limitation
		}
		i = 0;
		limitation_iter = limitation_begin(primitive);
		while (has_next(&limitation_iter))
		{
			limitation = limitation_next(&limitation_iter);
			render_limitation_item(limitation, i++);
		}
		nk_tree_pop(g_nk_context);
	}
}

static void	update_limitation(const t_limitation *old_limitation,
const t_limitation *new_limitation, const t_claddress addr_offset,
const t_buff_target buff_target)
{
	t_bool	up_to_date;

	up_to_date = ft_memcmp(old_limitation, new_limitation, sizeof(t_limitation)) == 0;
	if (up_to_date)
		return ;
	scenebuffer_map(&g_main_scene, addr_offset,
	sizeof(t_limitation), buff_target);
	scenebuffer_put(&g_main_scene, (void*)new_limitation, 0, sizeof(t_limitation));
	scenebuffer_unmap(&g_main_scene, buff_target);
}

void		render_limitation_form(const t_limitation *limitation,
const t_claddress addr_offset, const t_buff_target buff_target)
{
	t_limitation	new_limitation;
	t_bool			is_relative;

	if (nk_tree_push(g_nk_context, NK_TREE_TAB, "Limitation", NK_MAXIMIZED))
	{
		new_limitation = *limitation;
		nk_checkbox_label(g_nk_context, "Is local", &is_relative);
		new_limitation.is_relative = is_relative;
		update_limitation(limitation, &new_limitation, addr_offset, buff_target);
		nk_tree_pop(g_nk_context);
	}
}
