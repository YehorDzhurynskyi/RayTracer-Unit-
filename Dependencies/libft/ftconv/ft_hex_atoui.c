/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_atoui.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 16:29:26 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/12/25 15:24:05 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_hex_atoui(const char *s)
{
	unsigned int	n;

	n = 0;
	if (!s)
		return (0);
	if (s[0] == '0' && s[1] == 'x')
		s += 2;
	while (ft_ishex(*s))
	{
		if (ft_isdigit(*s))
			n = n * 16 + *s++ - '0';
		else if (*s >= 'A' && *s <= 'F')
			n = n * 16 + *s++ - 'A' + 10;
		else
			n = n * 16 + *s++ - 'a' + 10;
	}
	return (n);
}
