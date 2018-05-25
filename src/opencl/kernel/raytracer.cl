/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cl                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/opencl/kernel/shape.cl"

__kernel void trace(
	__global unsigned int *outputbuffer,
	t_camera camera
	// __constant void *scenebuffer,
)
{
	int	x = get_global_id(0);
	int	y = get_global_id(1);
	int width = get_global_size(0);
	int height = get_global_size(1);
	t_ray primary_ray = (t_ray){};
	float fov = tan(30.0f * M_PI / 180.0f);
	float xd = (2.0f * ((x + 0.5f) / width) - 1.0) * fov * (width / (float)height);
	float yd = (1.0 - 2.0 * ((y + 0.5) / height)) * fov;
	primary_ray.origin = camera.position;
	primary_ray.direction = (float4)(xd, yd, -1.0f, 0.0f);
	primary_ray.direction = normalize(primary_ray.direction);
	primary_ray.direction = mat4x4_mult_vec4(camera.rotation_matrix,
	primary_ray.direction);

	float t;

	t_shape shape;
	shape.color = (uchar4)(0, 0, 0, 0);
	shape.position = (float4)(0.0, 0.0, 0.0, 0.0);
	shape.shapetype = SPHERE;
	shape.buffer_offset = 0;

	t_sphere sphere;
	sphere.radius2 = 1.0f;

	if (sphere_intersect(&primary_ray, &shape, &sphere, &t) && t > 0.00001)
		outputbuffer[x + y * width] = 0x00FF0000;
	else
		outputbuffer[x + y * width] = 0x00000000;
}
