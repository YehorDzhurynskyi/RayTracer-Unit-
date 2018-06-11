/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_popups.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 18:07:32 by pzubar            #+#    #+#             */
/*   Updated: 2018/05/29 18:07:35 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_SDL_GL2_IMPLEMENTATION
#define NK_PRIVATE

#include <SDL.h>
#include <SDL_opengl.h>
#include "nuklear.h"
#include "nuklear_sdl.h"

extern struct nk_context	*g_nk_context;
extern struct nk_image		gui_images[6];
static int				scene;
static int image_active;

void	scenes_controls(void)
{
	nk_layout_row_dynamic(g_nk_context, 25, 1);
	nk_label(g_nk_context, "New scene", NK_TEXT_LEFT);
	nk_layout_row_dynamic(g_nk_context, 220, 1);
	nk_image(g_nk_context, gui_images[scene]);
	nk_layout_row_dynamic(g_nk_context, 25, 1);
	if (nk_button_label(g_nk_context, "Change"))
	{
		printf("Change scene to %d-th!\n", scene);
		image_active = 0;
	}
	if (nk_button_label(g_nk_context, "CANCEL"))
		image_active = 0;
}

void		display_scenes(void)
{
	int				i;

	i = 0;
	if (nk_button_label(g_nk_context, "Change scene"))
		image_active = !image_active;
	if (image_active)
	{
		if (nk_popup_begin(g_nk_context, NK_POPUP_STATIC, "Image Popup", 0, nk_rect(190, 30, 320, 515)))
		{
			nk_layout_row_dynamic(g_nk_context, 80, 3);
			while (i < 6)
			{
				if (nk_button_image(g_nk_context, gui_images[i]))
				{
					scene = i;
					nk_popup_close(g_nk_context);
				}
				i++;
			}
		}
		scenes_controls();
		nk_popup_end(g_nk_context);
	}
}

/*
void	display_loading()
{
// if (show_app_about && nk_begin(gui->g_nk_context, "Loading", nk_rect(500, 100, 0, 0),
	// 		NK_WINDOW_TITLE))
	// {
	// 	static struct nk_rect s = {0, 0, 300, 120};
	// 	if (nk_popup_begin(gui->g_nk_context, NK_POPUP_STATIC, "Loading", NK_WINDOW_TITLE|NK_WINDOW_BORDER, s))
	// 	{
	// 		nk_layout_row_dynamic(gui->g_nk_context, 25, 1);
	// 		if (prog_value < 50)
	// 			nk_label(gui->g_nk_context, "Step 1", NK_TEXT_LEFT);
	// 		else
	// 			nk_label(gui->g_nk_context, "Step 2", NK_TEXT_LEFT);
	// 			nk_progress(gui->g_nk_context, &prog_value, 100, NK_MODIFIABLE);
	// 			nk_popup_end(gui->g_nk_context);
	// 	}
	// }	
	// if (show_app_about)
	// 	nk_end(gui->g_nk_context);
}
*/
