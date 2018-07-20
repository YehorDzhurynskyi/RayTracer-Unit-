/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_object_form.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 13:59:40 by pzubar            #+#    #+#             */
/*   Updated: 2018/07/05 13:59:42 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_OBJECT_FORM_H
# define GUI_OBJECT_FORM_H

# include "gui.h"

void	render_shape_form(const t_shape *shape);
void	render_primitive_form(const t_primitive *primitive);
void	render_actual_primitive_form(const t_primitive *primitive);
void	render_sphere_form(const t_sphere *sphere);
void	render_cylinder_form(const t_cylinder *cylinder);
void	render_cone_form(const t_cone *cone);
void	render_lightsource_form(const t_lightsource *lightsource);
void	render_material_form(const t_material *material);

#endif
