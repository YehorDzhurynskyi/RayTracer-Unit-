/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#undef BUFF_SIZE
#define BUFF_SIZE	1024

char	*ft_read_file(const char *filename)
{
	char	buff[BUFF_SIZE + 1];
	int		fd;
	ssize_t	ret;
	char	*result;
	char	*temp;

	result = ft_strdup("");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		temp = ft_strjoin(result, buff);
		free(result);
		result = temp;
	}
	if (ret < 0)
	{
		free(result);
		return (NULL);
	}
	close(fd);
	return (result);
}
