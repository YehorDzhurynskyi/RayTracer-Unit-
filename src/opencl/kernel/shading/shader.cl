/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.cl                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_rcolor	shade(const t_scene *scene, const t_scene_buffers *buffers,
__read_only image2d_array_t textures, const t_fragment *fragment)
{
	t_rcolor color = fragment->diffuse_albedo * scene->config.ambient;
	t_iterator lightsrc_iter = lightsource_begin(scene, buffers);
	while (has_next(&lightsrc_iter))
	{
		__constant t_lightsource *lightsrc = lightsource_next(&lightsrc_iter);
		const t_rcolor	ill = illuminate(lightsrc, fragment) * lightsrc->intensity;
		const t_rcolor	dim = dimness(scene, buffers, textures, lightsrc, fragment, ill) * lightsrc->intensity;
		// printf("dim: %f %f %f %f\n", dim.x, dim.y, dim.z, dim.w);
		// printf("ill: %f %f %f %f\n", ill.x, ill.y, ill.z, ill.w);
		color += dim;
		// printf("col: %f %f %f %f\n", color.x, color.y, color.z, color.w);
	}
	return (color);
}
