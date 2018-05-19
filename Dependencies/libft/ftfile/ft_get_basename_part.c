/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_basename_part.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 15:25:03 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:56:33 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_file.h"
#include "libft.h"

#include <stdio.h>

char	*ft_get_basename_part(const char *filepath)
{
	char	*last_slash;

	last_slash = ft_strchrn(filepath, '/', -1);
	if (!last_slash)
		return ((char *)filepath);
	if (!*(last_slash + 1))
	{
		last_slash = ft_strchrn(filepath, '/', -2);
		if (!last_slash)
			return ((char *)filepath);
	}
	return (last_slash + 1);
}
