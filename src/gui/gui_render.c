/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/05/28 16:48:36 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

extern int				g_frame_width;
extern int				g_frame_height;
extern t_byte			*g_pixelbuffer;
extern struct nk_image	g_gui_render_target_image;

static void				render_fps(float mseconds)
{
	nk_layout_space_begin(g_nk_context, NK_STATIC, 20, 1);
	nk_layout_space_push(g_nk_context, nk_rect(20, 20, 100, 30));
	nk_labelf_colored(g_nk_context, NK_TEXT_LEFT,
		nk_rgba(253, 184, 19, 255), "%4d fps", (int)(1000 / mseconds));
	nk_labelf_colored(g_nk_context, NK_TEXT_LEFT,
		nk_rgba(253, 184, 19, 255), "%.2f ms", mseconds);
	nk_layout_space_end(g_nk_context);
}

void					gui_render_scene(float mseconds)
{
	struct nk_command_buffer	*canvas;
	struct nk_rect				rect;

	if (nk_begin(g_nk_context, "Render Target", nk_rect(SCENE_X, SCENE_Y,
	SCENE_WIDTH, SCENE_HEIGHT), g_nk_window_flags))
	{
		rect.x = SCENE_X + SCENE_PADDING;
		rect.y = SCENE_Y + SCENE_PADDING;
		rect.w = SCENE_WIDTH - 2.0f * SCENE_PADDING;
		rect.h = SCENE_HEIGHT - 2.0f * SCENE_PADDING;
		canvas = nk_window_get_canvas(g_nk_context);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, g_frame_width, g_frame_height,
		GL_RGBA, GL_UNSIGNED_BYTE, g_pixelbuffer);
		nk_draw_image(canvas, rect, &g_gui_render_target_image,
		nk_rgba(255, 255, 255, 255));
		render_fps(mseconds);
	}
	nk_end(g_nk_context);
}

void					gui_render(void)
{
	gui_render_scene_menu();
	gui_render_info_log();
	gui_render_scene_tree();
	gui_render_object();
	nk_sdl_render(NK_ANTI_ALIASING_OFF);
}
