/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vfx_toggle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vfx.h"
#include "renderer.h"

void	vfx_toggle_bw(void)
{
	if (BW_ENABLED(g_scene_renderer.vfx_mask))
		g_scene_renderer.vfx_mask &= ~BW_MASK;
	else
		g_scene_renderer.vfx_mask |= BW_MASK;
}

void	vfx_toggle_sepia(void)
{
	if (SEPIA_ENABLED(g_scene_renderer.vfx_mask))
		g_scene_renderer.vfx_mask &= ~SEPIA_MASK;
	else
		g_scene_renderer.vfx_mask |= SEPIA_MASK;
}

void	vfx_toggle_blur(void)
{
	if (BLUR_ENABLED(g_scene_renderer.vfx_mask))
		g_scene_renderer.vfx_mask &= ~BLUR_MASK;
	else
		g_scene_renderer.vfx_mask |= BLUR_MASK;
}

void	vfx_toggle_cartoon(void)
{
	if (CARTOON_ENABLED(g_scene_renderer.vfx_mask))
		g_scene_renderer.vfx_mask &= ~CARTOON_MASK;
	else
		g_scene_renderer.vfx_mask |= CARTOON_MASK;
	g_main_scene.config.cartoon_vfx_enabled = CARTOON_ENABLED(
		g_scene_renderer.vfx_mask);
}
