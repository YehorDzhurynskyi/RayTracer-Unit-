/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_info_log.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 17:34:37 by pzubar            #+#    #+#             */
/*   Updated: 2018/05/29 17:34:39 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

#define INFOLOG_BUFFER_SIZE	4096

static char		g_infolog_buffer[INFOLOG_BUFFER_SIZE];
static int		g_infolog_msg_count = 0;
static size_t	g_infolog_size = 0;

static void		info_log_append(const char *message, size_t size)
{
	ft_strncpy(g_infolog_buffer + g_infolog_size, message, INFOLOG_BUFFER_SIZE - g_infolog_size);
	g_infolog_size += INFOLOG_BUFFER_SIZE - g_infolog_size >= size ? size : INFOLOG_BUFFER_SIZE - g_infolog_size;
}

void			gui_info_log_error(const char *message, const char *err_code_message)
{
	size_t	message_len;
	size_t	err_code_message_len;

	message_len = ft_strlen(message);
	err_code_message_len = ft_strlen(err_code_message);
	if (12 + message_len + err_code_message_len + g_infolog_size >= INFOLOG_BUFFER_SIZE)
	{
		g_infolog_msg_count = 0;
		g_infolog_size = 0;
	}
	info_log_append("[ERROR - ", 9);
	info_log_append(err_code_message, err_code_message_len);
	info_log_append("]: ", 3);
	info_log_append(message, message_len + 1);
	g_infolog_msg_count++;
}

void			gui_info_log_notify(const char *message)
{
	size_t	message_len;

	message_len = ft_strlen(message);
	if (8 + message_len + g_infolog_size >= INFOLOG_BUFFER_SIZE)
	{
		g_infolog_msg_count = 0;
		g_infolog_size = 0;
	}
	info_log_append("[INFO]: ", 8);
	info_log_append(message, message_len + 1);
	g_infolog_msg_count++;
}

void			gui_render_info_log(void)
{
	char	*next_message;
	size_t	message_size;
	int		i;

	if (nk_begin(g_nk_context, "Information log",
	nk_rect(LOG_X, LOG_Y, LOG_WIDTH, LOG_HEIGHT), g_nk_window_flags | NK_WINDOW_TITLE))
	{
		gui_choose_opencl_device();
		gui_render_loading();
		nk_layout_row_dynamic(g_nk_context, 30, 1);
		next_message = g_infolog_buffer;
		i = 0;
		while (i++ < g_infolog_msg_count)
		{
			message_size = ft_strlen(next_message);
			nk_text_wrap(g_nk_context, next_message, message_size);
			next_message += message_size + 1;
		}
	}
	nk_end(g_nk_context);
}
