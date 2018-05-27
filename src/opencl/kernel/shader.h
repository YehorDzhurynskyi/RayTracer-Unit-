/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.hcl                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_HCL
# define SHADER_HCL

typedef struct s_fragment	t_fragment;
struct					s_fragment
{
	t_vec4				point;
	t_vec4				normal;
	t_vec4				to_eye;
	uchar4				color;
};

uchar4	shade(const t_vec4 *point, const t_scene *scene, __constant t_shape *shape);

# include "src/opencl/kernel/color.cl"
# include "src/opencl/kernel/light.h"

#endif
