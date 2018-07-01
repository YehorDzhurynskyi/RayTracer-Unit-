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

t_scalar	dimness(const t_vec4 *point, const t_scene *scene,
const t_scene_buffers *buffers, __constant t_lightsource *lightsrc)
{
	const t_vec4 to_light = to_lightsource(lightsrc, point);
	const t_vec4 shadow_ray_direction = normalize(to_light);
	const t_scalar bias = 0.005f;
	t_ray	shadow_ray = (t_ray){*point + shadow_ray_direction * bias, shadow_ray_direction};
	t_scalar t;
	__constant t_shape *nearest_shape = cast_ray(scene, buffers, &shadow_ray, &t);
	if (nearest_shape != NULL)
	{
		__constant t_material *material = get_material(buffers, nearest_shape);
		const t_scalar opacity = get_opacity(material->diffuse_albedo.color);
		if (lightsrc->lightsource_type == POINTLIGHT)
			return (pointlightsource_is_in_shadow(&to_light, t) * opacity);
		else if (lightsrc->lightsource_type == DIRLIGHT)
			return (dirlightsource_is_in_shadow() * opacity);
		else if (lightsrc->lightsource_type == SPOTLIGHT)
		{
			__constant t_spotlightsource *spotlight = (__constant t_spotlightsource*)lightsource_get_actual(lightsrc);
			return (spotlightsource_is_in_shadow(spotlight, &to_light, t) * opacity);
		}
	}
	return (0.0);
}
