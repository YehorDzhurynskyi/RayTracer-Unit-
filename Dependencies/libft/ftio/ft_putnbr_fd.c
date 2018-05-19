/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 17:00:56 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/10/28 16:45:42 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
}

void		ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putnbr_fd(-21, fd);
		ft_putnbr_fd(47483648, fd);
		return ;
	}
	if (n < 0)
	{
		n = -n;
		ft_putchar('-', fd);
	}
	if (n / 10 == 0)
	{
		ft_putchar(n + '0', fd);
		return ;
	}
	ft_putnbr_fd(n / 10, fd);
	ft_putchar(n % 10 + '0', fd);
}
