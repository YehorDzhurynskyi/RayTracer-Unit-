/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_foreach.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson.h"

inline static void	print_primitive_value(const t_cson *cson)
{
	if (cson->value_type == CSON_UNDEFINED_VALUE_TYPE)
		ft_printf(" undefined");
	else if (cson->value_type == CSON_STRING_VALUE_TYPE)
		ft_printf(" str(%s)", cson->value.string);
	else if (cson->value_type == CSON_INTEGER_VALUE_TYPE)
		ft_printf(" int(%d)", cson->value.integer);
	else if (cson->value_type == CSON_REAL_VALUE_TYPE)
		ft_printf(" real(%f)", cson->value.real);
	else if (cson->value_type == CSON_BOOLEAN_VALUE_TYPE)
		ft_printf(" bool(%s)", cson->value.boolean == FALSE ? "false" : "true");
}

inline static void	print_composite_value(const t_cson *cson)
{
	if (cson->value_type == CSON_OBJECT_VALUE_TYPE)
	{
		ft_printf(" (object)");
		if (cson->value.tuple->size == 0)
			ft_printf(" {}");
	}
	else if (cson->value_type == CSON_ARRAY_VALUE_TYPE)
	{
		ft_printf(" (array)");
		if (cson->value.tuple->size == 0)
			ft_printf(" []");
	}
}

static void			print_node(const t_cson *cson)
{
	int	depth;

	if (cson->parent == NULL)
		return ;
	depth = cson_depth(cson) - 1;
	while (depth--)
		ft_putchar('\t');
	ft_printf("\"%s\":", cson->key);
	if (cson->value_type == CSON_OBJECT_VALUE_TYPE
	|| cson->value_type == CSON_ARRAY_VALUE_TYPE)
		print_composite_value(cson);
	else
		print_primitive_value(cson);
	ft_putchar('\n');
}

void				cson_print(const t_cson *cson)
{
	if (cson == NULL)
	{
		ft_printf("(null)\n");
		return ;
	}
	cson_foreach(cson, print_node);
}
