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
# include <SDL.h>
# include <SDL_opengl.h>

void	window_create(void);
void	window_loop(void);
void	camera_key_handler(t_camera *camera);
const t_shape	*pick_shape(const SDL_MouseButtonEvent *event, t_scene *scene);
void	window_cleanup(void);

#endif
