/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 15:47:55 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/10/27 14:31:10 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strequ(char const *s1, char const *s2)
{
	unsigned char *u1;
	unsigned char *u2;

	if (!s1 || !s2)
		return (0);
	u1 = (unsigned char *)s1;
	u2 = (unsigned char *)s2;
	while (*u1)
		if (*u1++ != *u2++)
			return (0);
	if (*u2)
		return (0);
	return (1);
}
