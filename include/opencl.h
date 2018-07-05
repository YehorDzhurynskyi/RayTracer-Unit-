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

# include "ft.h"

typedef cl_uchar4	t_clcolor;

typedef cl_int		t_claddress;
typedef cl_int		t_clresourceid;
typedef cl_int		t_clbool;
typedef cl_float	t_clscalar;
typedef cl_float3	t_clvec3;
typedef cl_float4	t_clvec4;
typedef cl_float16	t_clmat4x4;

# define NULL_RESOURCE_ID	0

typedef struct s_opencl	t_opencl;
struct					s_opencl
{
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	command_queue;
};

typedef struct s_opencl_program	t_opencl_program;
struct					s_opencl_program
{
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				outputbuffer;
};

void					opencl_init(void);
void					opencl_cleanup(void);
t_opencl_program		opencl_program_create(const char *sourcefile,
const char *kernel_name);
void					opencl_program_cleanup(t_opencl_program *clprogram);
const char				*opencl_get_error(int error);

t_vec3d					opencl_vec3_to_vec3(t_clvec3 vec);
t_vec3d					opencl_vec4_to_vec3(t_clvec4 vec);
t_vec4d					opencl_vec4_to_vec4(t_clvec4 vec);
t_mat4d					opencl_mat4x4_to_mat4x4(t_clmat4x4 mat);

extern t_opencl			g_clcontext;

#endif
