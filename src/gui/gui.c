/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/05/28 16:48:36 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "logger.h"

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_SDL_GL2_IMPLEMENTATION
#define NK_PRIVATE

#define IMGNUM 9

#include <sys/stat.h>

#include <SDL.h>
#include <SDL_opengl.h>
#include "nuklear.h"
#include "nuklear_sdl.h"

#include "targa.h"
#include <time.h>

extern struct nk_context	*g_nk_context;
struct nk_image				g_gui_images[9];
static unsigned int			g_gl_image_textures[9];
extern int					g_frame_width;
extern int					g_frame_height;

int		show_devices(void)
{
	int			i;
	static int	active;
	char		*devices;

	i = 0;
	devices = "device_1\0device_2\0device_3\0";
	while (*devices)
	{
		if (nk_option_label(g_nk_context, devices, active == i))
			active = i;
		i++;
		devices += ft_strlen(devices) + 1;
	}
	return (active);
}

void	display_opencl_choice(void)
{
	static t_bool	display_needed = TRUE;
	int				active;

	if (display_needed == FALSE)
		return ;
	if (nk_popup_begin(g_nk_context, NK_POPUP_STATIC, "Device", 0,
		nk_rect(POPUP_X, 30, POPUP_WIDTH, 170)))
	{
		nk_layout_row_dynamic(g_nk_context, 25, 1);
		nk_label(g_nk_context, "Choose OpenCL device", NK_TEXT_LEFT);
		active = show_devices();
		if (nk_button_label(g_nk_context, "CHOOSE"))
		{
			display_needed = FALSE;
			//set active
		}
	}
	nk_popup_end(g_nk_context);
}

void	screen_shot(void)
{
	time_t	now;
	t_byte	*pixels;
	int		inflen;
	char	inf[256];

	time(&now);
	inflen = ft_strlen(RT_CWD "/Screenshots/");
	ft_memcpy(&inf, RT_CWD "/Screenshots/", inflen);
	ft_memcpy(&inf[inflen], ctime(&now), 24);
	inflen += 24;
	ft_memcpy(&inf[inflen], ".bmp\0", 5);
	inflen += 4;
	ft_strreplallchr(inf, ' ', '_');
	pixels = malloc(sizeof(t_byte) * ((g_frame_width * g_frame_height) * 3));
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
	mkdir(RT_CWD "/Screenshots", S_IRWXU | S_IRWXG | S_IRWXO);
	tga_write_rgb(inf, pixels, (uint16_t)g_frame_width,
		(uint16_t)g_frame_height, 24);
	ft_memcpy(&inf[inflen], " was saved!\0", 12);
	log_notify(inf);
	free(pixels);
}

void	ui_init_images(void)
{
	int			i;
	char		buffer[32];
	char		*num;
	SDL_Surface	*surf;

	i = 0;
	while (i < IMGNUM && (num = nk_itoa(num, i)))
	{
		g_gl_image_textures[i] = i;
		ft_memcpy(&buffer, "../../img/img", 13);
		ft_memcpy(&buffer[13], num, ft_strlen(num));
		ft_memcpy(&buffer[13 + ft_strlen(num)], ".bmp", 4);
		surf = SDL_LoadBMP(buffer);
		if (!surf && printf("No texture file\n"))
			exit(-1);
		glGenTextures(1, &g_gl_image_textures[i]);
		glBindTexture(GL_TEXTURE_2D, g_gl_image_textures[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surf->w, surf->h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, surf->pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		g_gui_images[i] = nk_image_id(g_gl_image_textures[i]);
		SDL_FreeSurface(surf);
		i++;
	}
}

void	render_gui(void)
{
	display_mainmnu();
	display_console();
	display_shapes_win();
	display_object_win();
}
