/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "logger.h"

cl_mem	create_image(const cl_image_format format,
const cl_image_desc desc, void *pixels)
{
	cl_mem	mem_obj;
	int		err;

	mem_obj = clCreateImage(g_clcontext.context, CL_MEM_READ_ONLY
	| CL_MEM_HOST_WRITE_ONLY | CL_MEM_COPY_HOST_PTR, &format, &desc,
	pixels, &err);
	if (err != CL_SUCCESS)
		log_error(opencl_get_error(err), RT_OPENCL_ERROR);
	return (mem_obj);
}
