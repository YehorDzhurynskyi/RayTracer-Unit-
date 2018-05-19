/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "ft.h"
#include <stdlib.h>
#include <errno.h>

void	print_error(const char *message)
{
	ft_printf_fd(2, "RT Error: %s\n", message);
	// if (errno != 0)
	// 	ft_printf_fd(2, "\t%s\n", strerror(errno));
	exit(EXIT_FAILURE);
}

void	print_opencl_error(const char *message, int cl_error_code)
{
	ft_printf_fd(2, "OpenCL Error[%d]: %s\n", cl_error_code, message);

	// TODO: shutdown opencl context
	//		clReleaseCommandQueue(cl->commands);
	//		clReleaseContext(cl->context);

	exit(EXIT_FAILURE);
}
