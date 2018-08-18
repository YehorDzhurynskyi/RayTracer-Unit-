/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_ends_with.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 16:45:53 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/10/27 14:30:04 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	ft_str_ends_with(const char *str, const char *needle)
{
	size_t	str_len;
	size_t	needle_len;

	str_len = ft_strlen(str);
	needle_len = ft_strlen(needle);
	return (ft_strequ(str + str_len - needle_len, needle));
}
