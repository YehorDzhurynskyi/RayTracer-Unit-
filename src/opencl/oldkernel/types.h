/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef uchar4	t_color;

typedef unsigned char	t_byte;

typedef int		t_address;
# define NULL	((void*)0)

typedef int		t_resourceid;

typedef int		t_bool;
# define TRUE	1
# define FALSE	0

typedef float	t_scalar;
typedef float3	t_vec3;
typedef float4	t_vec4;
typedef float16	t_mat4x4;

typedef struct
{
	t_vec4		origin;
	t_vec4		direction;
}	t_ray;

#endif
