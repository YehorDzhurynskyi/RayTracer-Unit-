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
__read_only image2d_array_t textures, const t_vec4 *point, __constant t_shape *shape)
{
	t_fragment	fragment;
	__constant t_material *material = get_material(buffers, shape);
	__constant t_primitive *primitive = (__constant t_primitive*)shape_get_primitive(shape);

	fragment.point = *point;
	fragment.normal = obtain_normal(point, shape);
	fragment.to_eye = normalize(scene->camera.position - primitive->position);
	t_scalar u, v;
	obtain_uv(primitive, point, &fragment.normal, &u, &v);
	if (DIFFUSE_IS_TEX(material->mask))
		fragment.diffuse_albedo = texture_map(buffers, textures, material->diffuse_albedo.tex_addr, u, v);
	else
		fragment.diffuse_albedo = color2rcolor(material->diffuse_albedo.color);
	if (SPECULAR_IS_TEX(material->mask))
		fragment.specular_albedo = texture_map(buffers, textures, material->specular_albedo.tex_addr, u, v);
	else
		fragment.specular_albedo = color2rcolor(material->specular_albedo.color);
	if (HAS_NORMAL_MAP(material->mask))
	{
		t_vec4 new_normal = texture_map(buffers, textures, material->normal_map, u, v);
		new_normal.x -= 0.5f;
		new_normal.y -= 0.5f;
		new_normal.w = 0.0f;
		new_normal = normalize(new_normal);
		fragment.normal = normal_map(fragment.normal, new_normal);
	}
	if (GLOSSINESS_IS_TEX(material->mask))
		fragment.glossiness = texture_map(buffers, textures, material->glossiness.tex_addr, u, v).r;
	else
		fragment.glossiness = material->glossiness.value;
	return (fragment);
}

t_rcolor	shade(const t_vec4 *point, const t_ray *ray, const t_scene *scene,
const t_scene_buffers *buffers, __read_only image2d_array_t textures, __constant t_shape *shape)
{
	t_fragment fragment = compose_fragment(scene, buffers, textures, point, shape);
	t_rcolor color = color_scalar(fragment.diffuse_albedo, scene->config.ambient);
	__constant t_primitive *primitive = (__constant t_primitive*)shape_get_primitive(shape);
	if (dot(fragment.normal, ray->direction) > 0.0)
	{
		if (primitive->primitive_type != PLANE)
			return (0);
		fragment.normal = -fragment.normal;
	}
	t_iterator lightsrc_iter = lightsource_begin(scene, buffers);
	while (has_next(&lightsrc_iter))
	{
		__constant t_lightsource *lightsrc = lightsource_next(&lightsrc_iter);
		// TODO: add soft shadows
		color = color_add(color, color_scalar(illuminate(lightsrc, &fragment),
		lightsrc->intensity * (1.0f - dimness(point, scene, buffers, lightsrc, shape))));
	}
	return (color);
}
