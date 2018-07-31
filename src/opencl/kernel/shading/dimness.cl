// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   dimness.cl                                         :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
// /*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// t_scalar	dimness(const t_scene *scene, const t_scene_buffers *buffers, __read_only image2d_array_t textures,
// __constant t_lightsource *lightsrc, const t_fragment *fragment);

// t_scalar	dimness(const t_scene *scene, const t_scene_buffers *buffers, __read_only image2d_array_t textures,
// __constant t_lightsource *lightsrc, const t_fragment *fragment)
// {
// 	const t_vec4 to_light = to_lightsource(lightsrc, &fragment->point);
// 	if (dot(to_light, fragment->normal) < 0.0f)
// 		return (1.0f);
// 	const t_vec4 shadow_ray_direction = normalize(to_light);
// 	const t_scalar bias = 0.005f;
// 	t_ray shadow_ray = (t_ray){fragment->point + shadow_ray_direction * bias, shadow_ray_direction};
// 	t_scalar t;
// 	__constant t_shape *nearest_shape = cast_ray(scene, buffers, &shadow_ray, &t);
// 	if (nearest_shape != NULL)
// 	{
// 		const t_fragment fragment = compose_fragment(scene, buffers, textures, nearest_shape, &shadow_ray, t);
// 		const t_scalar opacity = 1.0f - fragment.diffuse_albedo.a;
// 		if (lightsrc->lightsource_type == POINTLIGHT)
// 			return (pointlightsource_is_in_shadow(&to_light, t) * opacity);
// 		else if (lightsrc->lightsource_type == DIRLIGHT)
// 			return (dirlightsource_is_in_shadow() * opacity);
// 		else if (lightsrc->lightsource_type == SPOTLIGHT)
// 		{
// 			__constant t_spotlightsource *spotlight = (__constant t_spotlightsource*)lightsource_get_actual(lightsrc);
// 			return (spotlightsource_is_in_shadow(spotlight, &to_light, t) * opacity);
// 		}
// 	}
// 	return (0.0f);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dimness.cl                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_rcolor	dimness(const t_scene *scene, const t_scene_buffers *buffers, __read_only image2d_array_t textures,
__constant t_lightsource *lightsrc, const t_fragment *fragment, const t_rcolor init_color);

t_rcolor	dimness(const t_scene *scene, const t_scene_buffers *buffers, __read_only image2d_array_t textures,
__constant t_lightsource *lightsrc, const t_fragment *fragment, const t_rcolor init_color)
{
	t_scalar			t;
	t_ray				next_ray;
	t_fragment 			next_fragment = *fragment;
	t_rcolor			result_color = init_color;
	t_scalar			opacity = 1.0f;
	int					trace_depth = scene->config.trace_depth;
	const t_scalar		bias = 0.005f;

	// TODO: count refraction
	do {
		const t_vec4 to_light = to_lightsource(lightsrc, &next_fragment.point);
		next_ray.direction = normalize(to_light);
		next_ray.origin = next_fragment.point + next_ray.direction * (dot(to_light, next_fragment.normal) < 0.0f ? -bias : bias);
		__constant t_shape *nearest_shape = cast_ray(scene, buffers, &next_ray, &t);
		if (nearest_shape == NULL)
			break;
		if (lightsrc->lightsource_type == POINTLIGHT && pointlightsource_is_in_shadow(&to_light, t) == FALSE)
			break;
		else if (lightsrc->lightsource_type == DIRLIGHT && dirlightsource_is_in_shadow() == FALSE)
			break;
		else if (lightsrc->lightsource_type == SPOTLIGHT && spotlightsource_is_in_shadow((__constant t_spotlightsource*)lightsource_get_actual(lightsrc), &to_light, t) == FALSE)
			break;
		next_fragment = compose_fragment(scene, buffers, textures, nearest_shape, &next_ray, t);
		const t_scalar nearest_shape_opacity = 1.0f - next_fragment.diffuse_albedo.a;
		result_color += next_fragment.diffuse_albedo * opacity * nearest_shape_opacity;
		result_color *= color2rcolor(lightsrc->color) * (1.0f - nearest_shape_opacity);
		if (nearest_shape_opacity == 1.0f)
			return (result_color);
		opacity *= (1.0f - nearest_shape_opacity);
	} while (--trace_depth > 0);
	return (result_color);
}

