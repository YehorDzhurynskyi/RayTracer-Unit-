/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_choose_device.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/05/28 16:48:36 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "logger.h"
#include "renderer.h"
#include <pthread.h>
#include "window.h"

#define RT_MAX_CL_DEVICE_COUNT		4
#define RT_MAX_CL_DEVICE_NAME_LEN	255

static int	choose_devices(int ndevices)
{
	static int		active = -1;
	cl_device_id	devices[RT_MAX_CL_DEVICE_COUNT];
	char			device_name[RT_MAX_CL_DEVICE_NAME_LEN];
	int				err;
	int				i;

	ndevices = ndevices > RT_MAX_CL_DEVICE_COUNT ? RT_MAX_CL_DEVICE_COUNT : ndevices;
	err = clGetDeviceIDs(NULL, CL_DEVICE_TYPE_ALL, ndevices, devices, NULL);
	if (err != CL_SUCCESS)
		log_fatal(opencl_get_error(err), RT_OPENCL_ERROR);
	i = -1;
	while (++i < ndevices)
	{
		clGetDeviceInfo(devices[i], CL_DEVICE_NAME, RT_MAX_CL_DEVICE_NAME_LEN, device_name, NULL);
		if (nk_option_label(g_nk_context, device_name, active == i))
		{
			g_clcontext.device_id = devices[i];
			active = i;
		}
	}
	return (active);
}

void		gui_choose_opencl_device(void)
{
	static t_bool	render_widget = TRUE;
	int				ndevices;
	int				err;
	int				active;
	pthread_t		renderer_init_thread;

	if (render_widget == FALSE)
		return ;
	err = clGetDeviceIDs(NULL, CL_DEVICE_TYPE_ALL, 0, NULL, (unsigned int*)&ndevices);
	if (err != CL_SUCCESS)
	{
		window_error(RT_APP_NAME " OpenCL error", "No device that support OpenCL");
		log_fatal(opencl_get_error(err), RT_OPENCL_ERROR);
	}
	if (nk_popup_begin(g_nk_context, NK_POPUP_STATIC, "Device", 0,
		nk_rect(DEV_CHOOSE_POP_X, DEV_CHOOSE_POP_Y, DEV_CHOOSE_POP_WIDTH, 50 * ndevices + 55)))
	{
		nk_layout_row_dynamic(g_nk_context, 30, 1);
		nk_label(g_nk_context, "Choose OpenCL device to compile raytracer kernel", NK_TEXT_RIGHT);
		active = choose_devices(ndevices);
		if (nk_button_label(g_nk_context, "Compile") && active >= 0)
		{
			render_widget = FALSE;
			pthread_create(&renderer_init_thread, NULL, (void* (*)(void*))renderer_init, NULL);
			pthread_detach(renderer_init_thread);
		}
	}
	nk_popup_end(g_nk_context);
}
