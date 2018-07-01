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

typedef float	t_scalar;

typedef float3	t_vec3;


typedef float16	t_mat4x4;
typedef float4	t_vec4;

# define NULL	((void*)0)

typedef int	t_bool;
typedef uchar4	t_color;

# define TRUE	1
# define FALSE	0

typedef unsigned char	t_byte;

typedef struct s_ray	t_ray;
struct				s_ray
{
	t_vec3			origin;
	t_vec3			direction;
};

t_vec4				mat4x4_mult_vec4(const t_mat4x4 mat, const t_vec4 vec);
t_vec3				mat4x4_mult_vec3(const t_mat4x4 mat, const t_vec3 vec);
t_vec3				reflect3(t_vec3 v, t_vec3 n);
t_vec4				reflect4(t_vec4 v, t_vec4 n);

# include "src/opencl/kernel/math.cl"

#endif
