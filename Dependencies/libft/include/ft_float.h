/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 15:35:58 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/11/15 15:19:05 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FLOAT_H
# define FT_FLOAT_H

# include "libft.h"
# include <float.h>
# include <stdint.h>

# define FT_FMNT	(uint32_t)(((uint32_t)1 << (FLT_MANT_DIG - 1)) - 1)
# define FT_FEXP	(0xFF)
# define FT_DMNT	(uint64_t)(((uint64_t)1 << (DBL_MANT_DIG - 1)) - 1)
# define FT_DEXP	(0x7FF)
# define FT_LDMNT	(uint64_t)(((uint64_t)1 << (LDBL_MANT_DIG - 1)) - 1)
# define FT_LDEXP	(0x7FFF)
# define FT_DEXPDIG (11)

unsigned	ft_get_ffrac(char *dest, unsigned precision, float f);
unsigned	ft_get_dfrac(char *dest, unsigned precision, double d);
unsigned	ft_get_ldfrac(char *dest, unsigned precision, long double ld);
t_bool		is_fnan(float f);
t_bool		is_dnan(double d);
t_bool		is_ldnan(long double ld);
t_bool		is_finf(float f);
t_bool		is_dinf(double d);
t_bool		is_ldinf(long double ld);
t_bool		is_fneg(float f);
t_bool		is_dneg(double d);
t_bool		is_ldneg(long double ld);

#endif
