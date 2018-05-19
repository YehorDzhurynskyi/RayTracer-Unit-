/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 12:58:02 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/11/17 14:40:13 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include "ft_amap.h"

#define BUFF_SIZE 1024

static void	process_rest(char **old_str, char const *str)
{
	char	*temp;

	if (!*str)
		return ;
	if (*old_str)
	{
		temp = *old_str;
		*old_str = ft_strjoin(*old_str, str);
		ft_strdel(&temp);
	}
	else
		*old_str = ft_strdup(str);
}

static int	process_str(char const *str, char **s_old_str, char **line)
{
	char	*end;
	char	*sub;

	end = ft_strchr(str, '\n');
	if (!end)
	{
		process_rest(s_old_str, str);
		return (0);
	}
	sub = ft_strsub(str, 0, end - str);
	if (!sub)
		*line = ft_strdup(*s_old_str);
	else if (!*s_old_str)
		*line = ft_strdup(sub);
	else
		*line = ft_strjoin(*s_old_str, sub);
	ft_strdel(&sub);
	ft_strdel(s_old_str);
	process_rest(s_old_str, end + 1);
	if (!*line)
		return (-1);
	return (1);
}

static int	process_old_str(char **old_str, char **line)
{
	char	*end;
	char	*temp;

	end = ft_strchr(*old_str, '\n');
	if (!end)
		return (0);
	*line = ft_strsub(*old_str, 0, end - *old_str);
	temp = *old_str;
	*old_str = ft_strdup(end + 1);
	if (!**old_str)
		ft_strdel(old_str);
	ft_strdel(&temp);
	if (!*line)
		return (-1);
	return (1);
}

static int	process_line(char **old_str, char **line, int fd)
{
	int		res;
	char	*buff;
	int		ret;

	if (*old_str && (res = process_old_str(old_str, line)) != 0)
		return (res);
	buff = (char *)malloc(sizeof(char) * (BUFF_SIZE) + 1);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		res = process_str(buff, old_str, line);
		if (res)
			break ;
	}
	ft_strdel(&buff);
	if (!(ret > 0))
		res = ret < 0 ? -1 : 0;
	if (res == 0 && *old_str)
	{
		*line = ft_strdup(*old_str);
		ft_strdel(old_str);
		return (1);
	}
	return (res);
}

int			get_next_line(int fd, char **line)
{
	static t_amap	*s_map = NULL;
	char			**old_str;
	int				ret;

	if (fd < 0 || !line)
		return (-1);
	if (!s_map)
		s_map = amap_create(3);
	if (!amap_contains(s_map, fd))
	{
		old_str = (char **)malloc(sizeof(char *));
		*old_str = NULL;
		amap_put(s_map, fd, old_str);
	}
	old_str = (char **)amap_get(s_map, fd);
	ret = process_line(old_str, line, fd);
	if (ret == 0)
	{
		amap_remove(s_map, fd, NULL);
		free(old_str);
	}
	return (ret);
}
