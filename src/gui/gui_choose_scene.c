/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_choose_scene.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 18:07:32 by pzubar            #+#    #+#             */
/*   Updated: 2018/05/29 18:07:35 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "logger.h"
#include <dirent.h>
#include "scene.h"
#include <pthread.h>

static const char	*render_scene_list(const char *scenenames, int scenesnum)
{
	static int	active = -1;
	int			i;
	const char	*choosen_scene_name;

	choosen_scene_name = NULL;
	i = -1;
	while (++i < scenesnum)
	{
		if (nk_option_label(g_nk_context, scenenames, active == i))
		{
			active = i;
			choosen_scene_name = scenenames;
		}
		scenenames += ft_strlen(scenenames) + 1;
	}
	return (choosen_scene_name);
}

static t_bool		render_pop_scenes(const char *scenenames, int scenesnum)
{
	int			scene_height;
	const char	*choosen_scene_name;
	t_bool		render_widget;
	pthread_t	scene_change_thread;

	render_widget = TRUE;
	scene_height = (scenesnum / 2) * 30 + 65;
	nk_popup_begin(g_nk_context, NK_POPUP_STATIC, "Choose scene file", 0,
						nk_rect(SCENE_COOSE_POP_X, SCENE_COOSE_POP_Y, SCENE_COOSE_POP_WIDTH, scene_height));
	nk_layout_row_dynamic(g_nk_context, 25, 1);
	nk_label(g_nk_context, "Choose scene", NK_TEXT_RIGHT);
	nk_layout_row_dynamic(g_nk_context, 25, 2);
	choosen_scene_name = render_scene_list(scenenames, scenesnum);
	nk_layout_row_dynamic(g_nk_context, 25, 2);
	if (nk_button_label(g_nk_context, "Cancel"))
		render_widget = FALSE;
	if (nk_button_label(g_nk_context, "Change") && choosen_scene_name != NULL)
	{
		render_widget = FALSE;
		gui_loading_start("Loading scene...");
		pthread_create(&scene_change_thread, NULL, (void* (*)(void*))scene_change, (void*)choosen_scene_name);
		pthread_detach(scene_change_thread);
	}
	nk_popup_end(g_nk_context);
	return (render_widget);
}

static size_t		scenenames_length(void)
{
	DIR				*dir;
	struct dirent	*entry;
	size_t			length;

	length = 0;
	dir = opendir(SCENE_DIR);
	while ((entry = readdir(dir)) != NULL)
	{
		if (ft_strstr(entry->d_name, ".cson"))
			length += ft_strlen(entry->d_name) + 1;
	}
	closedir(dir);
	return (length);
}

static char			*load_scenenames(int *num)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*scenenames;
	char			*buffer_ptr;

	*num = 0;
	scenenames = malloc(sizeof(char) * scenenames_length());
	if (scenenames == NULL)
		return (NULL);
	buffer_ptr = scenenames;
	dir = opendir(SCENE_DIR);
	while ((entry = readdir(dir)) != NULL)
	{
		if (ft_strstr(entry->d_name, ".cson"))
		{
			ft_memcpy(buffer_ptr, entry->d_name, ft_strlen(entry->d_name) + 1);
			buffer_ptr += ft_strlen(entry->d_name) + 1;
			(*num)++;
		}
	}
	closedir(dir);
	return (scenenames);
}

void				gui_choose_scene(void)
{
	static int		scenesnum = 0;
	static t_bool	render_chooser = FALSE;
	static char		*scenenames = NULL;

	if (nk_button_label(g_nk_context, "Choose scene from file"))
	{
		scenenames = load_scenenames(&scenesnum);
		if (scenenames == NULL)
			log_error("Couldn't allocate enough memory"
			" to show scene list", RT_MEM_ALLOC_ERROR);
		render_chooser = scenenames != NULL;
	}
	if (render_chooser)
	{
		render_chooser = render_pop_scenes(scenenames, scenesnum);
		if (render_chooser == FALSE)
			free(scenenames);
	}
}
