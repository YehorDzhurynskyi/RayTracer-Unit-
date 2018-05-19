/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:29:42 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/10/25 19:50:59 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char *cdst;
	char *csrc;

	cdst = (char *)dst;
	csrc = (char *)src;
	while (n--)
		cdst[n] = csrc[n];
	return (dst);
}
