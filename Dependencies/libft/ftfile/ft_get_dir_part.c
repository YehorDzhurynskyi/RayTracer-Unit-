/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_dir_part.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 15:18:14 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/03 15:24:44 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_file.h"
#include "libft.h"

char	*ft_get_dir_part(const char *filepath)
{
	char	*last_slash;

	last_slash = ft_strrchr(filepath, '/');
	if (!last_slash)
		return (ft_strdup(""));
	return (ft_strsub(filepath, 0, last_slash - filepath));
}
