/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 14:49:36 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/12/26 14:39:46 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERSION_H
# define CONVERSION_H

# include "libft.h"
# include <stdarg.h>

enum				e_length_mode
{
	lm_h = 1,
	lm_hh,
	lm_l,
	lm_ll,
	lm_z,
	lm_j,
	lm_ptrdiff,
	lm_upper_l
};

typedef enum e_length_mode	t_length_mode;

enum				e_type
{
	type_percent = 1,
	type_c,
	type_C,
	type_s,
	type_S,
	type_p,
	type_d,
	type_i,
	type_b,
	type_o,
	type_x,
	type_u,
	type_X,
	type_D,
	type_O,
	type_U,
	type_f,
	type_g,
	type_e,
	type_F,
	type_G,
	type_E,
	type_n
};

typedef enum e_type	t_type;

struct				s_conversion
{
	int				precision;
	int				field_width;
	int				zero_flag;
	int				apostrophe_flag;
	int				hash_flag;
	int				minus_flag;
	int				plus_flag;
	int				space_flag;
	t_type			type;
	unsigned int	shift;
	int				is_valid;
	t_length_mode	length_mode;
	int				dot_present;
};

typedef struct s_conversion	t_conversion;

struct				s_option
{
	int				*variable;
	int				value;
	int				shift;
};

typedef struct s_option	t_option;

t_conversion		get_conversion(const char *format);

#endif
