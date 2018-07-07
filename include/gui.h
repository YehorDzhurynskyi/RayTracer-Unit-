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

# include "ft.h"
# include "sceneiterator.h"

# define GAP			5.0

# define MENU_X			GAP
# define MENU_Y			GAP
# define MENU_WIDTH		300
# define MENU_HEIGHT	540

# define TREE_X			GAP
# define TREE_Y			(MENU_Y + MENU_HEIGHT + GAP)
# define TREE_WIDTH		MENU_WIDTH
# define TREE_HEIGHT	345

# define SCENE_X		(MENU_X + MENU_WIDTH + GAP)
# define SCENE_Y		GAP
# define SCENE_WIDTH	820
# define SCENE_HEIGHT	640
# define SCENE_PADDING	16.0

# define OBJ_X			(SCENE_X + SCENE_WIDTH + GAP)
# define OBJ_Y			GAP
# define OBJ_WIDTH		MENU_WIDTH
# define OBJ_HEIGHT		890

# define LOG_X			SCENE_X
# define LOG_Y			(SCENE_Y + SCENE_HEIGHT + GAP)
# define LOG_WIDTH		SCENE_WIDTH
# define LOG_HEIGHT		245

// # define CMD_X			(LOG_X + LOG_WIDTH + GAP)
// # define CMD_Y			(OBJ_Y + OBJ_HEIGHT + GAP)
// # define CMD_WIDTH		OBJ_WIDTH
// # define CMD_HEIGHT		TREE_HEIGHT

# define WINDOW_WIDTH	(GAP + MENU_WIDTH + GAP + SCENE_WIDTH + GAP + OBJ_WIDTH + GAP)
# define WINDOW_HEGHT	(OBJ_Y + OBJ_HEIGHT + GAP)

void	render_gui(void);
void	display_mainmnu(void);
void	display_console(void);
void	ui_init_images(void);
void	display_scenes(void);
void	display_shapes_win(void);
void	display_object_win(void);
void	select_object(t_claddress addr);
void	screen_shot(void);
void	show_shapes(void);
void	display_input_win(void);
void	loading_message(char *message);
void	loading_stop(void);
void	display_fps(float mseconds);

#endif
