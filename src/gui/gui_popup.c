/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_choose_scene.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 18:07:32 by pzubar            #+#    #+#             */
/*   Updated: 2018/05/29 18:07:35 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

t_bool	g_scene_interactive_enabled = TRUE;

void	gui_popup_start(void)
{
	g_scene_interactive_enabled = FALSE;
}

void	gui_popup_stop(void)
{
	g_scene_interactive_enabled = TRUE;
}
