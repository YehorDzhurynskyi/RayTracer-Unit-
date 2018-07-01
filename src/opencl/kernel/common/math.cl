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

t_vec3	mat4x4_mult_vec3(const t_mat4x4 mat, const t_vec3 vec)
{
	t_vec3	res;
	res.x = mat.s0 * vec.x + mat.s1 * vec.y + mat.s2 * vec.z;
	res.y = mat.s4 * vec.x + mat.s5 * vec.y + mat.s6 * vec.z;
	res.z = mat.s8 * vec.x + mat.s9 * vec.y + mat.sa * vec.z;
	return (res);
}

t_vec4	mat4x4_mult_vec4(const t_mat4x4 mat, const t_vec4 vec)
{
	t_vec4	res;
	res.x = mat.s0 * vec.x + mat.s1 * vec.y + mat.s2 * vec.z + mat.s3 * vec.w;
	res.y = mat.s4 * vec.x + mat.s5 * vec.y + mat.s6 * vec.z + mat.s7 * vec.w;
	res.z = mat.s8 * vec.x + mat.s9 * vec.y + mat.sa * vec.z + mat.sb * vec.w;
	res.w = mat.sc * vec.x + mat.sd * vec.y + mat.se * vec.z + mat.sf * vec.w;
	return (res);
}

t_vec3	reflect3(const t_vec3 incident, const t_vec3 normal)
{
	return (reflect4((t_vec4){incident, 0.0f}, (t_vec4){normal, 0.0f}).xyz);
}

t_vec4	reflect4(const t_vec4 incident, const t_vec4 normal)
{
	return (normalize(incident - (normal * (2.0f * dot(incident, normal)))));
}

t_vec3	refract3(t_vec3 incident, t_vec3 normal, t_scalar ior)
{
	return (refract4((t_vec4){incident, 0.0f}, (t_vec4){normal, 0.0f}, ior).xyz);
}

t_vec4	refract4(t_vec4 incident, t_vec4 normal, t_scalar ior)
{
	t_scalar	cosi = dot(incident, normal); 
	t_scalar	snell;
	if (cosi < 0)
	{
		cosi = -cosi;
		snell = 1.0f / ior; // here 1.0f is ior of vacuum
	}
	else
	{
		normal = -normal;
		snell = ior;
	}
	t_scalar	k = 1 - snell * snell * (1 - cosi * cosi); 
	return (k < 0 ? 0 : snell * incident + (snell * cosi - sqrt(k)) * normal);
}
