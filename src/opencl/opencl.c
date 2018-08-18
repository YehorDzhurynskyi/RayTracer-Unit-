/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/06/27 17:20:01 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opencl.h"
#include "logger.h"
#include "ft.h"

t_opencl	g_clcontext;

static void	opencl_error_callback(const char *errinfo,
const void *private_info, size_t cb, void *user_data)
{
	(void)user_data;
	ft_printf_fd(2, "OPENCL CALLBACK FUNCTION: "
	"%s\n[%zu] -> %s\n", errinfo, cb, private_info);
}

void		opencl_init(void)
{
	int	err;

	g_clcontext.context = clCreateContext(NULL, 1,
	&g_clcontext.device_id, opencl_error_callback, NULL, &err);
	if (g_clcontext.context == NULL || err != CL_SUCCESS)
		log_fatal(opencl_get_error(err), RT_OPENCL_ERROR);
	g_clcontext.command_queue = clCreateCommandQueue(g_clcontext.context,
	g_clcontext.device_id, 0, &err);
	if (g_clcontext.command_queue == NULL || err != CL_SUCCESS)
		log_fatal(opencl_get_error(err), RT_OPENCL_ERROR);
}

void		opencl_cleanup(void)
{
	clReleaseCommandQueue(g_clcontext.command_queue);
	clReleaseContext(g_clcontext.context);
	clReleaseDevice(g_clcontext.device_id);
}
