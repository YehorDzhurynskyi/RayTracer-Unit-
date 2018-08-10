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

struct nk_color			to_nkcolor(t_clcolor color);
t_clcolor				from_nkcolor(struct nk_color color);

void					render_shape_form(const t_shape *shape);
void					render_primitive_form(const t_shape *shape, const t_primitive *primitive);
void					render_actual_primitive_form(const t_shape *shape, const t_primitive *primitive);
void					render_sphere_form(const t_shape *shape, const t_sphere *sphere);
void					render_cylinder_form(const t_shape *shape, const t_cylinder *cylinder);
void					render_cone_form(const t_shape *shape, const t_cone *cone);
void					render_quadric_form(const t_shape *shape, const t_quadric_surface *quadric_surface);
void					render_material_form(const t_material *material);
void					render_texture_form(const t_texture *texture);
void					render_chess_texture_form(const t_texture *texture);
void					render_climage_texture_form(const t_texture *texture);
void					render_limitations(const t_shape *shape, const t_primitive *primitive);
void					render_lightsource_form(const t_lightsource *lightsource);
void					render_pointlightsource_form(const t_lightsource *lightsource,
const t_pointlightsource *pointlightsrc);
void					render_dirlightsource_form(const t_lightsource *lightsource,
const t_dirlightsource *dirlightsrc);
void					render_spotlightsource_form(const t_lightsource *lightsource,
const t_spotlightsource *spotlightsrc);

extern struct nk_color	property_color;

#endif
