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

# define RT_MAX_FILTERS	4

typedef struct
{
	t_opencl_program	rt_prgm;
	t_opencl_program	filter_prgms[RT_MAX_FILTERS];
	unsigned int		nfilters;
	t_scene				scene;
}	t_renderer;

void					renderer_init(void);
void					renderer_render(unsigned char *pixelbuffer,
int width, int height);
void					renderer_cleanup(void);

extern t_renderer		g_scene_renderer;

#endif
