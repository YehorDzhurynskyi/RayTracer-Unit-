/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_material_tree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/05/28 16:48:36 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui_scene_tree.h"

static void	render_material_tree_item(
const t_material *material, int tree_item_id)
{
	char	caption[255];
	size_t	name_len;

	ft_strncpy(caption, "Material, id : ", 255);
	name_len = ft_strlen(caption);
	ft_itoa_cat(caption + name_len, 255 - name_len, tree_item_id);
	if (nk_tree_push_id(g_nk_context, NK_TREE_NODE,
		caption, NK_MINIMIZED, tree_item_id))
	{
		if (nk_button_label(g_nk_context, "Select"))
			gui_select_object(material->addr, MATERIALBUFF_TARGET);
		nk_tree_pop(g_nk_context);
	}
}

void		render_material_tree(void)
{
	const t_material	*material;
	t_iterator			iter;
	int					i;

	iter = material_begin(&g_main_scene);
	i = 0;
	while (has_next(&iter))
	{
		material = material_next(&iter);
		render_material_tree_item(material, i++);
	}
}
