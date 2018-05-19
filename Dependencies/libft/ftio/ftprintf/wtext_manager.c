/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wtext_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 14:49:36 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/12/26 14:39:46 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "text_manager.h"
#include "multibyte.h"
#include "output.h"

extern int	g_ftprintf_length;

void		print_wstr(t_conversion *c, const wchar_t *src)
{
	ssize_t	wlen;
	char	*mbsrc;

	if (!src)
	{
		print_str(c, 0, 0);
		return ;
	}
	wlen = wstrlen(src, c);
	if (wlen < 0)
	{
		g_ftprintf_length = -1;
		return ;
	}
	mbsrc = to_multibyte_str(src, wlen);
	print_str(c, mbsrc, wlen);
	ft_memdel((void **)&mbsrc);
}

void		print_wchar(t_conversion *c, wchar_t ch)
{
	char			src[4];
	unsigned int	size;

	size = to_multibyte(ch, src);
	if (!size)
	{
		g_ftprintf_length = -1;
		return ;
	}
	print(c, src, size);
}
