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

static t_fragment	compose_fragment(const t_scene *scene, const t_scene_buffers *buffers,
const t_vec4 *point, __constant t_shape *shape)
{
	t_fragment	fragment;
	__constant t_material *material = get_material(buffers, shape);
	__constant t_byte *ptr = (__constant t_byte*)shape;
	ptr += sizeof(t_shape);
	__constant t_primitive *primitive = (__constant t_primitive*)ptr;

	fragment.point = *point;
	fragment.normal = obtain_normal(point, shape);
	fragment.to_eye = normalize(scene->camera.position - primitive->position);
	fragment.diffuse_albedo = material->diffuse_albedo.color;
	fragment.specular_albedo = material->specular_albedo.color;
	fragment.glossiness = material->glossiness.value;
	return (fragment);
}

t_color	shade(const t_vec4 *point, const t_scene *scene,
const t_scene_buffers *buffers, __constant t_shape *shape)
{
	__constant t_material *material = get_material(buffers, shape);
	t_color color = color_scalar(material->diffuse_albedo.color, scene->config.ambient);
	const t_fragment fragment = compose_fragment(scene, buffers, point, shape);
	t_iterator lightsrc_iter = lightsource_begin(scene, buffers);
	while (has_next(&lightsrc_iter))
	{
		__constant t_lightsource *lightsrc = lightsource_next(&lightsrc_iter);
		// TODO: add soft shadows
		color = color_add(color, color_scalar(illuminate(lightsrc, &fragment),
		lightsrc->intensity * (1.0f - dimness(point, scene, buffers, lightsrc))));
	}
	return (color);
}
