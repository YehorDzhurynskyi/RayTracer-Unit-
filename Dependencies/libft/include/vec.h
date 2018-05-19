/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 11:30:46 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/12/13 13:33:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

/*
**	SINGLE PRECISION 3D Vector
*/
typedef struct
{
	float		x;
	float		y;
	float		z;
}				t_vec3f;

float			vec3f_dot(const t_vec3f *v1, const t_vec3f *v2);
float			vec3f_length(const t_vec3f *vec);
t_vec3f			vec3f_cross(const t_vec3f *v1, const t_vec3f *v2);
t_vec3f			vec3f_normalize(const t_vec3f *vec);
t_vec3f			vec3f_add(const t_vec3f *v1, const t_vec3f *v2);
t_vec3f			vec3f_sub(const t_vec3f *v1, const t_vec3f *v2);
t_vec3f			vec3f_scalar(const t_vec3f *v, float s);
t_vec3f			vec3f_mult(const t_vec3f *v1, const t_vec3f *v2);
void			vec3f_print(const int fd, t_vec3f const *v);
t_vec3f			vec3f_reflect(t_vec3f const *v, t_vec3f const *n);
unsigned int	vec3f2rgb(t_vec3f const *vec);
t_vec3f			rgb2vec3f(unsigned int rgb);
/*
**	DOUBLE PRECISION 3D Vector
*/
typedef struct
{
	double		x;
	double		y;
	double		z;
}				t_vec3d;

double			vec3d_dot(const t_vec3d *v1, const t_vec3d *v2);
double			vec3d_length(const t_vec3d *vec);
t_vec3d			vec3d_cross(const t_vec3d *v1, const t_vec3d *v2);
t_vec3d			vec3d_normalize(const t_vec3d *vec);
t_vec3d			vec3d_add(const t_vec3d *v1, const t_vec3d *v2);
t_vec3d			vec3d_sub(const t_vec3d *v1, const t_vec3d *v2);
t_vec3d			vec3d_scalar(const t_vec3d *v, double s);
t_vec3d			vec3d_mult(const t_vec3d *v1, const t_vec3d *v2);
void			vec3d_print(const int fd, t_vec3d const *v);
t_vec3d			vec3d_reflect(t_vec3d const *v, t_vec3d const *n);
unsigned int	vec3d2rgb(t_vec3d const *vec);
t_vec3d			rgb2vec3d(unsigned int rgb);
/*
**	SINGLE PRECISION 4D Vector
*/
typedef struct
{
	float		x;
	float		y;
	float		z;
	float		w;
}				t_vec4f;

float			vec4f_dot(const t_vec4f *v1, const t_vec4f *v2);
float			vec4f_length(const t_vec4f *vec);
t_vec4f			vec4f_normalize(const t_vec4f *vec);
t_vec4f			vec4f_add(const t_vec4f *v1, const t_vec4f *v2);
t_vec4f			vec4f_sub(const t_vec4f *v1, const t_vec4f *v2);
t_vec4f			vec4f_scalar(const t_vec4f *v, float s);
t_vec4f			vec4f_mult(const t_vec4f *v1, const t_vec4f *v2);
t_vec3f			vec4f_to_vec3f(const t_vec4f *v);
void			vec4f_print(const int fd, t_vec4f const *v);
t_vec4f			vec4f_reflect(t_vec4f const *v, t_vec4f const *n);
unsigned int	vec4f2rgba(t_vec4f const *vec);
t_vec4f			rgba2vec4f(unsigned int rgba);
/*
**	DOUBLE PRECISION 4D Vector
*/
typedef struct
{
	double		x;
	double		y;
	double		z;
	double		w;
}				t_vec4d;

double			vec4d_dot(const t_vec4d *v1, const t_vec4d *v2);
double			vec4d_length(const t_vec4d *vec);
t_vec4d			vec4d_normalize(const t_vec4d *vec);
t_vec4d			vec4d_add(const t_vec4d *v1, const t_vec4d *v2);
t_vec4d			vec4d_sub(const t_vec4d *v1, const t_vec4d *v2);
t_vec4d			vec4d_scalar(const t_vec4d *v, double s);
t_vec4d			vec4d_mult(const t_vec4d *v1, const t_vec4d *v2);
t_vec3d			vec4d_to_vec3d(const t_vec4d *v);
void			vec4d_print(const int fd, t_vec4d const *v);
t_vec4d			vec4d_reflect(t_vec4d const *v, t_vec4d const *n);
unsigned int	vec4d2rgba(t_vec4d const *vec);
t_vec4d			rgba2vec4d(unsigned int rgba);

#endif
