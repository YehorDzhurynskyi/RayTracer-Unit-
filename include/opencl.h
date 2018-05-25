/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENCL_H
# define OPENCL_H

# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/opencl.h>
# endif

typedef struct s_opencl	t_opencl;
struct					s_opencl
{
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	commands;
};

typedef struct s_opencl_program	t_opencl_program;
struct					s_opencl_program
{
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				outputbuffer;
};

typedef cl_float16		t_clmat4x4;
typedef cl_float4		t_clvec4;

typedef struct			__attribute__ ((packed)) s_camera
{
	t_clmat4x4			rotation_matrix;
	t_clvec4			position;
}	t_camera;

void					opencl_init(void);
void					opencl_cleanup(void);
t_opencl_program		opencl_program_create(const char *sourcefile,
const char *kernel_name);
void					opencl_program_cleanup(t_opencl_program *clprogram);

extern t_opencl			g_clcontext;

#endif
