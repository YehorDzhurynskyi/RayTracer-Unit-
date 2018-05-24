/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_program.c                                   :+:      :+:    :+:   */
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

#define BUILDLOG_BUFF_SIZE	4096

static void			build_program(t_opencl_program *clprogram)
{
	char	logbuffer[BUILDLOG_BUFF_SIZE + 1];
	size_t	ret_size;
	int		err;

	err = clBuildProgram(clprogram->program, 0, NULL, NULL, NULL, NULL);
	if (err != CL_SUCCESS)
	{
		clGetProgramBuildInfo(clprogram->program, g_clcontext.device_id,
		CL_PROGRAM_BUILD_LOG, sizeof(logbuffer), logbuffer, &ret_size);
		if (ret_size > BUILDLOG_BUFF_SIZE)
			ret_size = BUILDLOG_BUFF_SIZE;
		logbuffer[ret_size] = '\0';
		print_opencl_error(logbuffer, err);
	}
}

t_opencl_program	opencl_program_create(const char *sourcefile, const char *kernel_name)
{
	t_opencl_program	clprogram;
	int					err;
	char				*source;

	clprogram = (t_opencl_program){NULL, NULL, NULL};
	source = ft_read_file(sourcefile);
	if (source == NULL)
		print_error("Failed to read openCL source file...");
	clprogram.program = clCreateProgramWithSource(g_clcontext.context,
	1, (const char **)&source, NULL, &err);
	free(source);
	if (clprogram.program == NULL || err != CL_SUCCESS)
		print_opencl_error("Failed to create openCL program...", err);
	build_program(&clprogram);
	clprogram.kernel = clCreateKernel(clprogram.program, kernel_name, &err);
	if (clprogram.kernel == NULL || err != CL_SUCCESS)
		print_opencl_error("Failed to create openCL kernel...", err);
	return (clprogram);
}

void				opencl_program_cleanup(t_opencl_program *clprogram)
{
	clReleaseProgram(clprogram->program);
	clReleaseKernel(clprogram->kernel);
}
