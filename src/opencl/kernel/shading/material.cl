/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.cl                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

__constant t_material	*get_material(const t_scene_buffers *buffers, __constant t_shape *shape)
{
	return ((__constant t_material*)(buffers->materialbuffer + shape->material_addr));
}

t_scalar	get_opacity(t_color color)
{
	return (1.0f - color.a / 255.0f);
}
