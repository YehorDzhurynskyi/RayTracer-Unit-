/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limitation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIMITATION_H
# define LIMITATION_H

typedef enum
{
	XAXIS = 1,
	YAXIS,
	ZAXIS,
	LINEAR,
	SIN,
	RADIAL
}	t_limitation_type;

# define IS_AXIAL(type) (type == XAXIS || type == YAXIS || type == ZAXIS)

typedef struct			__attribute__ ((packed))
{
	t_bool				is_relative;
	t_bool				cutting;
	t_limitation_type	limitation_type;
}	t_limitation;

typedef struct			__attribute__ ((packed))
{
	t_scalar			limit;
	t_bool				apply_if_less;
}	t_axial_limitation;

#endif
