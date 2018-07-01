/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include "scene.h"

typedef void	(*t_render_callback)(const t_scene *scene,
unsigned char *pixelbuffer, int width, int height);

void	window_create(void);
void	window_loop(t_render_callback render_callback, t_scene *scene);
void	camera_key_handler(t_camera *camera);
void	window_cleanup(void);

#endif
