/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_H
# define VALIDATION_H

# include "scenerepo.h"

t_err_code	validate_scene(const t_cson *cson);

t_err_code	validate_camera(const t_cson *cson);

t_err_code	validate_lightsource(const t_cson *cson);
t_err_code	validate_dirlightsource(const t_cson *cson);
t_err_code	validate_pointlightsource(const t_cson *cson);
t_err_code	validate_spotlightsource(const t_cson *cson);

t_err_code	validate_limitations(const t_cson *cson);
t_err_code	validate_limitation(const t_cson *cson);
t_err_code	validate_axial_limitation(const t_cson *cson);

t_err_code	validate_material(const t_cson *cson);
t_err_code	validate_texture(const t_cson *cson);

t_err_code	validate_shape(const t_cson *cson);
t_err_code	validate_primitive(const t_cson *cson);
t_err_code	validate_sphere(const t_cson *cson);
t_err_code	validate_cylinder(const t_cson *cson);
t_err_code	validate_cone(const t_cson *cson);
t_err_code	validate_torus(const t_cson *cson);
t_err_code	validate_quadric_surface(const t_cson *cson);
t_err_code	validate_parallelepiped(const t_cson *cson);

t_err_code	validate_color_required(const t_cson *cson, const char *key);
t_err_code	validate_color_optional(const t_cson *cson, const char *key, const char *default_value_str);

t_err_code	validate_bool_required(const t_cson *cson, const char *key);
t_err_code	validate_bool_optional(const t_cson *cson, const char *key, const char *default_value_str);

t_err_code	validate_real_required(const t_cson *cson, const char *key);
t_err_code	validate_real_optional(const t_cson *cson, const char *key, const char *default_value_str);
t_err_code	validate_real_required_ranged(const t_cson *cson, const char *key, const double range[2]);
t_err_code	validate_real_optional_ranged(const t_cson *cson, const char *key, const double range[2], const char *default_value_str);

t_err_code	validate_int_required(const t_cson *cson, const char *key);
t_err_code	validate_int_optional(const t_cson *cson, const char *key, const char *default_value_str);

t_err_code	validate_string_required(const t_cson *cson, const char *key);
t_err_code	validate_string_optional(const t_cson *cson, const char *key, const char *default_value_str);

t_err_code	validate_vec3_required(const t_cson *cson, const char *key, t_bool normalize);
t_err_code	validate_vec3_optional(const t_cson *cson, const char *key, t_bool normalize, const char *default_value_str);

t_err_code	validate_orientation_required(const t_cson *cson, const char *key);
t_err_code	validate_orientation_optional(const t_cson *cson, const char *key, const char *default_angles_str);

t_err_code	validation_failed(const t_cson *cson, t_err_code err_code, const char *message);
t_err_code	validation_failed_parent(const t_cson *cson, const char *key, t_err_code err_code, const char *message);
t_err_code	validation_set_optional(const t_cson *cson, const char *key, const char *default_value_str);

#endif
