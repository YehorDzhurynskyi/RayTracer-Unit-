/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"
#include "gui.h"
#include "logger.h"

t_renderer		g_scene_renderer;
t_bool			g_should_redraw_scene = FALSE;

extern t_bool	g_window_should_close;
extern t_byte	*g_pixelbuffer;
extern int		g_frame_width;
extern int		g_frame_height;

void			renderer_init(void)
{
	gui_loading_start("Compiling kernel...");
	opencl_init();
	g_scene_renderer.vfx_mask = 0;
	g_scene_renderer.rt_prgm = opencl_program_create(RT_CWD
	"/src/opencl/kernel/raytracer.cl", "trace");
	g_scene_renderer.filter_prgms[BW_ID] = opencl_program_create(RT_CWD
	"/src/opencl/kernel/filters/bw_filter.cl", "filter");
	g_scene_renderer.filter_prgms[SEPIA_ID] = opencl_program_create(RT_CWD
	"/src/opencl/kernel/filters/sepia_filter.cl", "filter");
	g_scene_renderer.filter_prgms[BLUR_ID] = opencl_program_create(RT_CWD
	"/src/opencl/kernel/filters/blur_filter.cl", "filter");
	scene_init_memory();
	gui_loading_stop();
	while (!g_window_should_close)
	{
		renderer_render(&g_main_scene, g_pixelbuffer,
		g_frame_width, g_frame_height);
	}
}

void			renderer_cleanup(void)
{
	int	i;

	opencl_program_cleanup(&g_scene_renderer.rt_prgm);
	i = -1;
	while (++i < RT_MAX_FILTERS)
	{
		opencl_program_cleanup(&g_scene_renderer.filter_prgms[i]);
	}
	opencl_cleanup();
}
