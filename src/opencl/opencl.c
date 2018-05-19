/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opencl.h"
#include "error.h"
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
	int			err;

	err = clGetDeviceIDs(NULL, CL_DEVICE_TYPE_GPU, 1, &g_clcontext.device_id, NULL);
	if (CL_SUCCESS != err)
		print_opencl_error("Failed to get device IDS...", err);
	g_clcontext.context = clCreateContext(NULL, 1, &g_clcontext.device_id, opencl_error_callback, NULL, &err);
	if (g_clcontext.context == NULL || err != CL_SUCCESS)
		print_opencl_error("Failed to create openCL context...", err);
	g_clcontext.commands = clCreateCommandQueue(g_clcontext.context, g_clcontext.device_id, 0, &err);
	if (g_clcontext.commands == NULL || err != CL_SUCCESS)
		print_opencl_error("Failed to create a queue of commands...", err);
}

void		opencl_cleanup(void)
{
	clReleaseCommandQueue(g_clcontext.commands);
	clReleaseContext(g_clcontext.context);
}
