/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.cl                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef int	t_bool;

#define TRUE 1
#define FALSE 0

typedef float16	t_mat4x4;
typedef float4	t_vec4;

typedef struct s_ray	t_ray;
struct			s_ray
{
	t_vec4		origin;
	t_vec4		direction;
};

typedef struct	__attribute__ ((packed)) s_camera
{
	t_mat4x4	rotation_matrix;
	t_vec4		position;
}	t_camera;

t_vec4			mat4x4_mult_vec4(const t_mat4x4 mat, const t_vec4 vec)
{
	t_vec4	res;
	res.x = mat[0] * vec.x + mat[1] * vec.y + mat[2] * vec.z + mat[3] * vec.w;
	res.y = mat[4] * vec.x + mat[5] * vec.y + mat[6] * vec.z + mat[7] * vec.w;
	res.z = mat[8] * vec.x + mat[9] * vec.y + mat[10] * vec.z + mat[11] * vec.w;
	res.w = mat[12] * vec.x + mat[13] * vec.y + mat[14] * vec.z + mat[15] * vec.w;
	return (res);
}