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

# define RT_APP_NAME	"RayTracer-Unit-"

void	window_create(void);
void	window_loop(void);
void	window_cleanup(void);
void	window_error(const char *title, const char *message);
void	window_warning(const char *title, const char *message);
void	window_info(const char *title, const char *message);

#endif
