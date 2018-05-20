/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multibyte.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 14:49:36 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/12/26 14:39:46 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTIBYTE_H
# define MULTIBYTE_H

# include <wchar.h>
# include "conversion.h"
# include <sys/types.h>

unsigned int	to_multibyte(wchar_t ch, char *dst);
char			*to_multibyte_str(const wchar_t *src, ssize_t wlen);
ssize_t			wstrlen(const wchar_t *src, t_conversion *c);

#endif
