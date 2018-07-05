/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

# include "libft.h"

void	render_gui(void);
void	display_mainmnu(void);
void	display_console(void);
void	ui_init_images(void);
void	display_scenes(void);
void	display_shapes_win(void);
void    display_object_win(void);
//void	display_info(void);
int		scren_shot(void);

void display_info(void);

// void log_gui(const char *message);


#endif
