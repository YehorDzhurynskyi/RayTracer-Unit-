/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 17:50:15 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/10/27 14:42:01 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

static int	ft_isalnum(int c)
{
	return (ft_isdigit(c) || ft_isalpha(c));
}

int			ft_isprint(int c)
{
	return ((c >= 32 && c <= 39)
			|| (c >= 40 && c <= 47)
			|| ft_isalnum(c)
			|| (c >= 58 && c <= 63)
			|| c == 64
			|| (c >= 91 && c <= 95)
			|| c == 96
			|| (c >= 123 && c <= 126));
}
