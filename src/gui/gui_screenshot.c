/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_screenshot.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/05/28 16:48:36 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include <sys/stat.h>
#include <time.h>
#include "targa.h"
#include "logger.h"

extern int				g_frame_width;
extern int				g_frame_height;
extern t_byte			*g_pixelbuffer;

void	gui_screenshot(void)
{
	time_t	now;
	t_byte	*pixels;
	char	path[RT_GUI_RESOURCE_PATH_BUFF_LEN];

	now = time(NULL);
	ft_strncpy(path, RT_CWD "/Screenshots/", RT_GUI_RESOURCE_PATH_BUFF_LEN);
	ft_strlcat(path, ctime(&now), RT_GUI_RESOURCE_PATH_BUFF_LEN);
	path[ft_strlen(path) - 1] = '\0';
	ft_strlcat(path, ".bmp", RT_GUI_RESOURCE_PATH_BUFF_LEN);
	ft_strreplallchr(path, ' ', '_');
	pixels = malloc(sizeof(t_byte) * (g_frame_width * g_frame_height * 3));
	if (pixels == NULL)
		return ;
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
	mkdir(RT_CWD "/Screenshots", S_IRWXU | S_IRWXG | S_IRWXO);
	tga_write_rgb(path, pixels, (uint16_t)g_frame_width,
		(uint16_t)g_frame_height, 24);
	log_notify("Screenshot saved to: " RT_CWD "/Screenshots");
	free(pixels);
}
