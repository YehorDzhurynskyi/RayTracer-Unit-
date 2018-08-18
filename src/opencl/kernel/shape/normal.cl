/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.cl                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_vec4	obtain_normal(const t_vec4 *point, __constant t_shape *shape)
{
	// TODO: shape could be a composite so in this case need to handle relation types etc
	__constant t_primitive *primitive = shape_get_primitive(shape);
	t_vec4 normal = obtain_primitive_normal(point, primitive);
	// if (shape->relation_type == NEGATION)
	// 	normal = -normal;
	return (normal);
}

t_vec4	obtain_primitive_normal(const t_vec4 *point, __constant t_primitive *primitive)
{
	if (primitive->primitive_type == SPHERE)
		return (obtain_sphere_normal(point, primitive));
	else if (primitive->primitive_type == PLANE)
		return (obtain_plane_normal(point, primitive));
	else if (primitive->primitive_type == CONE)
		return (obtain_cone_normal(point, primitive));
	else if (primitive->primitive_type == CYLINDER)
		return (obtain_cylinder_normal(point, primitive));
	else if (primitive->primitive_type == TORUS)
		return (obtain_torus_normal(point, primitive));
	else if (primitive->primitive_type == QUADRIC)
		return (obtain_quadric_surface_normal(point, primitive));
	else if (primitive->primitive_type == PARALLELEPIPED)
		return (obtain_parallelepiped_normal(point, primitive));
	return (0);
}
