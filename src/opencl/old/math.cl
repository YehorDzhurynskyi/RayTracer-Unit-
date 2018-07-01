/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.cl                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_vec4	mat4x4_mult_vec4(const t_mat4x4 mat, const t_vec4 vec)
{
	t_vec4	res;
	res.x = mat[0] * vec.x + mat[1] * vec.y + mat[2] * vec.z + mat[3] * vec.w;
	res.y = mat[4] * vec.x + mat[5] * vec.y + mat[6] * vec.z + mat[7] * vec.w;
	res.z = mat[8] * vec.x + mat[9] * vec.y + mat[10] * vec.z + mat[11] * vec.w;
	res.w = mat[12] * vec.x + mat[13] * vec.y + mat[14] * vec.z + mat[15] * vec.w;
	return (res);
}

t_vec3	mat4x4_mult_vec3(const t_mat4x4 mat, const t_vec3 vec)
{
	t_vec3	res;
	res.x = mat[0] * vec.x + mat[1] * vec.y + mat[2] * vec.z;
	res.y = mat[4] * vec.x + mat[5] * vec.y + mat[6] * vec.z;
	res.z = mat[8] * vec.x + mat[9] * vec.y + mat[10] * vec.z;
	return (res);
}

t_vec4	reflect4(t_vec4 v, t_vec4 n)
{
	const t_vec4 r = n * (2.0f * dot(v, n));
	return (normalize(v - r));
}

t_vec3	reflect3(t_vec3 v, t_vec3 n)
{
	const t_vec3 r = n * (2.0f * dot(v, n));
	return (normalize(v - r));
}
