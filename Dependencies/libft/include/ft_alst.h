/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alst.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 15:24:25 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/12/26 13:39:23 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ALST_H
# define FT_ALST_H

# include "libft.h"

typedef struct
{
	size_t	capacity;
	size_t	size;
	void	**array;
}	t_alst;

t_alst		*alst_create(size_t capacity);
void		alst_add(t_alst *alst, void *content);
void		*alst_get(t_alst *alst, unsigned int i);
void		alst_iteri(t_alst *alst, void (*f)(void *content, unsigned int i));
t_bool		alst_remove(t_alst *alst, void (*clear)(void **item),
		unsigned int i);
void		alst_clear(t_alst *alst, void (*clear)(void **item));
void		alst_del(t_alst **alst);
void		*alst_to_array(t_alst *alst, void (*collector)(void *arr, void
			*item, unsigned int offset), size_t item_size);
int			alst_get_index(t_alst *alst,
void *content, t_bool (*eq)(void*, void*));

#endif
