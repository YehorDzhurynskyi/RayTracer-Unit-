/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

# include "opencl.h"
# include "scene.h"
# include "vfx.h"

# define RT_MAX_FILTERS	3
# define RT_MAX_VFX		(RT_MAX_FILTERS + 1)

typedef struct
{
	t_opencl_program	rt_prgm;
	t_vfx_mask			vfx_mask;
	t_opencl_program	filter_prgms[RT_MAX_FILTERS];
}	t_renderer;

void					renderer_init(void);
void					renderer_render(const t_scene *scene,
unsigned char *pixelbuffer, int width, int height);
void					renderer_cleanup(void);

extern t_bool			g_should_redraw_scene;
extern t_renderer		g_scene_renderer;

#endif
