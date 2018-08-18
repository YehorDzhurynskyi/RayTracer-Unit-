/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplallchr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 13:45:46 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/10/30 13:45:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

void	ft_strreplallchr(char *src, char from, char to)
{
	if (from == '\0' || to == '\0' || src == NULL)
		return ;
	while (*src)
	{
		if (*src == from)
			*src = to;
		src++;
	}
}
