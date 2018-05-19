/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_manager.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 14:49:36 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/12/26 14:39:46 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMBER_MANAGER_H
# define NUMBER_MANAGER_H

# include "conversion.h"
# include <stdarg.h>
# include "libft.h"

# define NBSIZE 128
# define FBSIZE	128

struct		s_nument
{
	size_t	size;
	size_t	prefix_len;
	size_t	int_len;
	size_t	frac_len;
	size_t	suffix_len;
};

typedef struct s_nument	t_nument;

void		print_integer(t_conversion *c);
void		print_hinteger(t_conversion *c);
void		print_hhinteger(t_conversion *c);
void		print_linteger(t_conversion *c);
void		print_llinteger(t_conversion *c);
void		print_zinteger(t_conversion *c);
void		print_jinteger(t_conversion *c);
void		print_tinteger(t_conversion *c);
void		print_real(t_conversion *c);
size_t		fill_integer(char *dest,
unsigned long long n, const t_conversion *c);
void		print_inumber(unsigned long long n,
int is_negative, t_conversion *c);
unsigned	get_base(const t_conversion *c);
char		*get_prefix(int is_negative,
const t_conversion *c, const char *num);
void		print_number(const char *prefix,
	const char *num, t_conversion *c);
void		print_nument(const char *prefix,
const char *suffix, const t_nument *ent, const t_conversion *c);

#endif
