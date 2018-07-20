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
# include "nuklear_sdl.h"

# define GAP				5.0

# define SCENEMENU_X		GAP
# define SCENEMENU_Y		GAP
# define SCENEMENU_WIDTH	300
# define SCENEMENU_HEIGHT	560

# define TREE_X				GAP
# define TREE_Y				(SCENEMENU_Y + SCENEMENU_HEIGHT + GAP)
# define TREE_WIDTH			SCENEMENU_WIDTH
# define TREE_HEIGHT		325

# define SCENE_X			(SCENEMENU_X + SCENEMENU_WIDTH + GAP)
# define SCENE_Y			GAP
# define SCENE_WIDTH		820
# define SCENE_HEIGHT		640
# define SCENE_PADDING		16.0

# define OBJ_X				(SCENE_X + SCENE_WIDTH + GAP)
# define OBJ_Y				GAP
# define OBJ_WIDTH			SCENEMENU_WIDTH
# define OBJ_HEIGHT			890

# define LOG_X				SCENE_X
# define LOG_Y				(SCENE_Y + SCENE_HEIGHT + GAP)
# define LOG_WIDTH			SCENE_WIDTH
# define LOG_HEIGHT			245

// # define CMD_X			(LOG_X + LOG_WIDTH + GAP)
// # define CMD_Y			(OBJ_Y + OBJ_HEIGHT + GAP)
// # define CMD_WIDTH		OBJ_WIDTH
// # define CMD_HEIGHT		TREE_HEIGHT

# define WINDOW_WIDTH	(GAP + SCENEMENU_WIDTH + GAP + SCENE_WIDTH + GAP + OBJ_WIDTH + GAP)
# define WINDOW_HEGHT	(OBJ_Y + OBJ_HEIGHT + GAP)

# define POPUP_X		(SCENE_X + SCENE_WIDTH / 2 - POPUP_WIDTH / 2)
# define POPUP_Y		(SCENE_Y + SCENE_HEIGHT / 4)
# define POPUP_WIDTH	400

# define RT_GUI_RESOURCE_PATH_BUFF_LEN	1024

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
void	loading_message(char *message);
void	loading_stop(void);
void	display_fps(float mseconds);
void	display_opencl_choice(void);
void	display_loading(void);
void 	display_corresponding_options(const t_primitive *prim);

void	gui_init(SDL_Window *win, GLuint render_target);
void	gui_poll_events(t_scene *scene);
void	gui_render_scene(float mseconds);
void	gui_render(void);
void	gui_render_scene_menu(void);
void	gui_render_info_log(void);
void	gui_render_scene_tree(void);
void	gui_render_object(void);
void	gui_cleanup(void);
void	gui_screenshot(void);
void	gui_choose_opencl_device(void);
void	gui_choose_scene(void);
void	gui_select_object(t_claddress addr, const t_buff_target target);
void	gui_render_color_picker(struct nk_colorf *target_color);
void	gui_init_style(void);

// TODO: move in another header?
void	camera_key_handler(t_camera *camera);
const t_shape	*pick_shape(const SDL_MouseButtonEvent *event, t_scene *scene);

extern struct nk_context	*g_nk_context;

#endif
