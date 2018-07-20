/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"
#include "window.h"
#include "renderer.h"
#include "scene.h"
#include "sceneeditor.h"
#include "scenerepository.h"
#include "shape.h"
#include <stdlib.h>
#include "logger.h"

void		atexit_callback(void)
{
	renderer_cleanup();
	system("leaks RT");
}

int			main(void)
{
	{ // TODO: replace on realease
		atexit(atexit_callback);
	}
	window_create();
	window_loop();
	window_cleanup();
	scene_cleanup(g_main_scene_ptr);
	// renderer_cleanup();
	return (EXIT_SUCCESS);
}
