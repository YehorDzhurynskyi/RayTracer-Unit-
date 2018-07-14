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
#define GUI_H

#define WINDOW_HGHT 900
#define GAP 5.0
#define MENU_W 300
#define MENU_H 540
#define MENU_X GAP
#define MENU_Y GAP
#define OBJ_X (GAP + MENU_W + GAP + SCENE_W + GAP)
#define OBJ_Y GAP
#define SCENE_X (GAP + MENU_W + GAP)
#define SCENE_Y GAP
#define SCENE_W 820
#define SCENE_HEIGHT 640
#define WINDOW_WDTH (GAP + MENU_W + GAP + SCENE_W + GAP + MENU_W + GAP)

#include "libft.h"
#include "sceneiterator.h"

void render_gui(void);
void display_mainmnu(void);
void display_console(void);
void ui_init_images(void);
void display_scenes(void);
void display_shapes_win(void);
void display_object_win(void);
void set_object(t_claddress addr);
int	scren_shot(void);
void show_shapes(void);
void display_input_win(void);
void loading_message(char *message);
void loading_stop(void);
void display_fps(float mseconds);

#endif
