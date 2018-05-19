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

# include <OpenCL/opencl.h>

typedef struct
{
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	commands;
}						t_opencl;

typedef struct
{
	cl_program			program;
	cl_kernel			kernel;
}						t_opencl_program;

void					opencl_init(void);
void					opencl_cleanup(void);
t_opencl_program		opencl_program_create(const char *file, const char *kernel);
void					opencl_program_cleanup(t_opencl_program *clprogram);

extern t_opencl			g_clcontext;

#endif
