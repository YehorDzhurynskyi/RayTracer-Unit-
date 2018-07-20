/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/05/28 16:48:36 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

extern t_bool	g_window_should_close;

void	gui_poll_events(t_scene *scene)
{
	SDL_Event	event;

	if (g_main_scene_ptr != NULL) // TODO: fixme
		camera_key_handler(&scene->camera);
	nk_input_begin(g_nk_context);
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			g_window_should_close = TRUE;
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
				g_window_should_close = TRUE;
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (g_main_scene_ptr != NULL) // TODO: fixme
				pick_shape(&event.button, scene);
		}
		nk_sdl_handle_event(&event);
	}
	nk_input_end(g_nk_context);
}
