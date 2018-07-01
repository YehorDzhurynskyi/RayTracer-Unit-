/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.cl                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static t_color		illuminate(__constant t_lightsource *lightsrc, const t_fragment *fragment)
{
	__constant t_byte *actual = lightsource_get_actual(lightsrc);
	if (lightsrc->lightsource_type == POINTLIGHT)
		return (pointlightsource_illuminate(lightsrc, (__constant t_pointlightsource*)actual, fragment));
	else if (lightsrc->lightsource_type == DIRLIGHT)
		return (dirlightsource_illuminate(lightsrc, (__constant t_dirlightsource*)actual, fragment));
	else if (lightsrc->lightsource_type == SPOTLIGHT)
		return (spotlightsource_illuminate(lightsrc, (__constant t_spotlightsource*)actual, fragment));
	return (0);
}

static t_fragment	compose_fragment(const t_scene *scene,
const t_vec4 *point, __constant t_shape *shape)
{
	t_fragment	fragment;
	__constant t_material *material = get_material(scene, shape);
	__constant t_primitive *primitive = shape_get_primitive(shape);

	fragment.point = *point;
	fragment.normal = obtain_normal(point, shape);
	fragment.to_eye = normalize(scene->camera.position - primitive->position);
	fragment.color = material->color;
	fragment.specularity = (1.0 - material->specularity.value) * 256.0;
	fragment.glossiness = material->glossiness.value;
	return (fragment);
}

t_color				shade(const t_vec4 *point, const t_scene *scene,
__constant t_shape *shape)
{
	__constant t_material *material = get_material(scene, shape);
	return (material->color);
	// t_color color = color_scalar(material->color, scene->config.ambient);
	// const t_fragment fragment = compose_fragment(scene, point, shape);
	// t_iterator lightsrc_iter = lightsource_begin(scene);
	// while (has_next(&lightsrc_iter))
	// {
	// 	__constant t_lightsource *lightsrc = lightsource_next(&lightsrc_iter);
	// 	color = color_add(color, illuminate(lightsrc, &fragment));
	// 	// color = color_add(color, color_scalar(illuminate(light_ptr, &fragment), 1.0f - dimness(point, scene, light_ptr)));
	// }
	// return (color);
}
