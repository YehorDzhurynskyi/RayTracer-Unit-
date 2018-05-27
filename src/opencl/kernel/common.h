/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.hcl                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_HCL
# define COMMON_HCL

typedef float16	t_mat4x4;
typedef float4	t_vec4;

# define NULL	((void*)0)

typedef int	t_bool;

# define TRUE	1
# define FALSE	0

typedef unsigned char	t_byte;

typedef struct s_ray	t_ray;
struct				s_ray
{
	t_vec4			origin;
	t_vec4			direction;
};

typedef struct	__attribute__ ((packed)) s_camera
{
	t_mat4x4		rotation_matrix;
	t_vec4			position;
}	t_camera;

typedef struct s_scene	t_scene;
struct					s_scene
{
	__constant t_byte	*shapebuffer;
	int					nshapes;
	__constant t_byte	*lightbuffer;
	int					nlights;
	t_camera			camera;
};

t_vec4				mat4x4_mult_vec4(const t_mat4x4 mat, const t_vec4 vec);
t_vec4				reflected_vec(t_vec4 v, t_vec4 n);

# include "src/opencl/kernel/math.cl"

#endif