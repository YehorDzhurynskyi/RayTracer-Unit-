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
#define WINDOW_WDTH 1440
#define X_CENTERED (WINDOW_WDTH / 2) - (820 / 2)  //aka 310

# include "libft.h"
#include "sceneiterator.h"

void	render_gui(void);
void	display_mainmnu(void);
void	display_console(void);
void	ui_init_images(void);
void	display_scenes(void);
void	display_shapes_win(void);
void    display_object_win(void);
void    set_object(t_claddress addr);
int		scren_shot(void);
void    show_shapes(void);
void    display_input_win(void);

// void log_gui(const char *message);


#endif
