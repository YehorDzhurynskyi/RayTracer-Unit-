/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 11:30:46 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/12/13 13:33:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPLEX_H
# define COMPLEX_H

struct		s_complex
{
	double	re;
	double	im;
};

typedef struct s_complex	t_complex;

t_complex	complex_add(const t_complex *z1, const t_complex *z2);
t_complex	complex_sub(const t_complex *z1, const t_complex *z2);
t_complex	complex_prod(const t_complex *z1, const t_complex *z2);
t_complex	complex_div(const t_complex *z1, const t_complex *z2);

#endif
