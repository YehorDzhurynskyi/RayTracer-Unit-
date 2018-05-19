/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   real_manager.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 14:49:36 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/12/26 14:39:46 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REAL_MANAGER_H
# define REAL_MANAGER_H

# include "libft.h"
# include "conversion.h"
# include "number_manager.h"

void		print_inf(t_bool is_neg, t_bool is_small, t_conversion *c);
void		print_nan(t_bool is_small, t_conversion *c);
char		*get_rnumber(const char *fbuff,
	size_t frac_len, unsigned long long integer, t_conversion *c);
unsigned	fill_lfraction(char *dest, long double n,
	const t_conversion *c, t_bool is_neg);
t_nument	get_flreal(long double n, t_conversion *c);
t_nument	get_elreal(long double n, t_conversion *c, int *ex);
t_nument	get_glreal(long double n, t_conversion *c, int *ex);
void		print_lrnumber(long double n, t_conversion *c);
t_bool		dot_present(size_t frac_len, const t_conversion *c);

#endif
