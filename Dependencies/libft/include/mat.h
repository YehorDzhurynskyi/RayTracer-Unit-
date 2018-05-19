/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:47:48 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/11/21 16:00:13 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAT_H
# define MAT_H

# include "vec.h"

/*
**	SINGLE PRECISION 3D Matrix
*/
typedef struct
{
	float	data[3][3];
}			t_mat3f;

t_mat3f		mat3f_identity(void);
t_mat3f		mat3f_create(const float *data);
t_mat3f		mat3f_mat3f_mult(const t_mat3f *m1, const t_mat3f *m2);
t_vec3f		mat3f_vec3f_mult(const t_mat3f *m, const t_vec3f *v);
t_vec3f		vec3f_mat3f_mult(const t_vec3f *v, const t_mat3f *m);
void		mat3f_print(const int fd, const t_mat3f *m);
float		mat3f_determinant(const float m[3][3]);
t_mat3f		mat3f_scalar(const t_mat3f *m, float s);
t_mat3f		mat3f_inverse(const t_mat3f *m);
t_mat3f		mat3f_transpose(const t_mat3f *m);
void		mat3f_minor(float dest[2][2], const float src[3][3], int r, int c);

/*
**	SINGLE PRECISION 3D Matrix
*/
typedef struct
{
	double	data[3][3];
}			t_mat3d;

t_mat3d		mat3d_identity(void);
t_mat3d		mat3d_create(const double *data);
t_mat3d		mat3d_mat3d_mult(const t_mat3d *m1, const t_mat3d *m2);
t_vec3d		mat3d_vec3d_mult(const t_mat3d *m, const t_vec3d *v);
t_vec3d		vec3d_mat3d_mult(const t_vec3d *v, const t_mat3d *m);
void		mat3d_print(const int fd, const t_mat3d *m);
double		mat3d_determinant(const double m[3][3]);
t_mat3d		mat3d_scalar(const t_mat3d *m, double s);
t_mat3d		mat3d_inverse(const t_mat3d *m);
t_mat3d		mat3d_transpose(const t_mat3d *m);
void		mat3d_minor(double dest[2][2],
const double src[3][3], int r, int c);

/*
**	SINGLE PRECISION 4D Matrix
*/
typedef struct
{
	float	data[4][4];
}			t_mat4f;

t_mat4f		mat4f_identity(void);
t_mat4f		mat4f_create(const float *data);
t_mat4f		mat4f_mat4f_mult(const t_mat4f *m1, const t_mat4f *m2);
t_vec4f		mat4f_vec4f_mult(const t_mat4f *m, const t_vec4f *v);
t_vec4f		vec4f_mat4f_mult(const t_vec4f *v, const t_mat4f *m);
void		mat4f_print(const int fd, const t_mat4f *m);
float		mat4f_determinant(const float m[4][4]);
t_mat4f		mat4f_scalar(const t_mat4f *m, float s);
t_mat4f		mat4f_inverse(const t_mat4f *m);
t_mat4f		mat4f_transpose(const t_mat4f *m);
void		mat4f_minor(float dest[3][3], const float src[4][4], int r, int c);

/*
**	DOUBLE PRECISION 4D Matrix
*/
typedef struct
{
	double	data[4][4];
}			t_mat4d;

t_mat4d		mat4d_identity(void);
t_mat4d		mat4d_create(const double *data);
t_mat4d		mat4d_mat4d_mult(const t_mat4d *m1, const t_mat4d *m2);
t_vec4d		mat4d_vec4d_mult(const t_mat4d *m, const t_vec4d *v);
t_vec4d		vec4d_mat4d_mult(const t_vec4d *v, const t_mat4d *m);
void		mat4d_print(const int fd, const t_mat4d *m);
double		mat4d_determinant(const double m[4][4]);
t_mat4d		mat4d_scalar(const t_mat4d *m, double s);
t_mat4d		mat4d_inverse(const t_mat4d *m);
t_mat4d		mat4d_transpose(const t_mat4d *m);
void		mat4d_minor(double dest[3][3],
const double src[4][4], int r, int c);

#endif
