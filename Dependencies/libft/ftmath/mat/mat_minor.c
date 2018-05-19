/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_minor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 10:40:58 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/11/21 15:49:23 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	mat3f_minor(float dest[2][2], const float src[3][3], int r, int c)
{
	int	i;
	int	j;
	int	cc;
	int	rr;

	i = -1;
	rr = 0;
	while (++i < 3)
	{
		if (i == r)
			continue ;
		j = -1;
		cc = 0;
		while (++j < 3)
		{
			if (j == c)
				continue ;
			dest[rr][cc++] = src[i][j];
		}
		rr++;
	}
}

void	mat3d_minor(double dest[2][2], const double src[3][3], int r, int c)
{
	int	i;
	int	j;
	int	cc;
	int	rr;

	i = -1;
	rr = 0;
	while (++i < 3)
	{
		if (i == r)
			continue ;
		j = -1;
		cc = 0;
		while (++j < 3)
		{
			if (j == c)
				continue ;
			dest[rr][cc++] = src[i][j];
		}
		rr++;
	}
}

void	mat4f_minor(float dest[3][3], const float src[4][4], int r, int c)
{
	int	i;
	int	j;
	int	cc;
	int	rr;

	i = -1;
	rr = 0;
	while (++i < 4)
	{
		if (i == r)
			continue ;
		j = -1;
		cc = 0;
		while (++j < 4)
		{
			if (j == c)
				continue ;
			dest[rr][cc++] = src[i][j];
		}
		rr++;
	}
}

void	mat4d_minor(double dest[3][3], const double src[4][4], int r, int c)
{
	int	i;
	int	j;
	int	cc;
	int	rr;

	i = -1;
	rr = 0;
	while (++i < 4)
	{
		if (i == r)
			continue ;
		j = -1;
		cc = 0;
		while (++j < 4)
		{
			if (j == c)
				continue ;
			dest[rr][cc++] = src[i][j];
		}
		rr++;
	}
}
