/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.cl                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_bool	shape_intersected(__constant t_shape *shape, const t_ray *ray, t_scalar *t)
{
	// TODO: shape could be a composite so in this case need to handle relation types etc
	return (primitive_intersected(shape_get_primitive(shape), ray, t));
}

t_bool	primitive_intersected(__constant t_primitive *primitive, const t_ray *ray, t_scalar *t)
{
	if (primitive->primitive_type == SPHERE)
		return (sphere_intersected(primitive, ray, t));
	else if (primitive->primitive_type == PLANE)
		return (plane_intersected(primitive, ray, t));
	else if (primitive->primitive_type == CONE)
		return (cone_intersected(primitive, ray, t));
	else if (primitive->primitive_type == CYLINDER)
		return (cylinder_intersected(primitive, ray, t));
	else if (primitive->primitive_type == COMPOSITE || primitive->primitive_type == POINT) // TODO: making an assumption that the point is infinitely small
		return (FALSE);

	// TODO: process limitations
	printf("Unrecognized primitive type : %d\n", primitive->primitive_type);
	return (FALSE);
}
