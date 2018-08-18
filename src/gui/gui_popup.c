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

void	gui_popup_start(void)
{
	g_nk_window_flags |= NK_WINDOW_NOT_INTERACTIVE;
}

void	gui_popup_stop(void)
{
	g_nk_window_flags &= ~NK_WINDOW_NOT_INTERACTIVE;
}
