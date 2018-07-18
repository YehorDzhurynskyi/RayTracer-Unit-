/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_shapes_win.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 18:07:37 by pzubar            #+#    #+#             */
/*   Updated: 2018/06/30 18:07:39 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_SDL_GL2_IMPLEMENTATION
#define NK_PRIVATE

#include <SDL.h>
#include <SDL_opengl.h>
#include "nuklear.h"
#include "nuklear_sdl.h"

extern struct nk_context *g_nk_context;
static const char *g_primitive_names[] = {"Composite", "Point", "Plane",
	"Sphere", "Cone", "Cylinder"};

void	show_sphere_cylinder_options(const t_byte *actual, t_primitive_type t)
{
	char				*name;
	const t_sphere		*sphere;
	const t_cylinder	*cylinder;
	static float		radius;

	name = (t == SPHERE) ? "Sphere" : "Cylinder";
	if (t == SPHERE)
		sphere = (const t_sphere*)actual;
	else
		cylinder = (const t_cylinder*)actual;
	if (nk_tree_push(g_nk_context, NK_TREE_TAB, name, NK_MAXIMIZED))
	{
		nk_layout_row_dynamic(g_nk_context, 30, 1);
		radius = (t == SPHERE) ?
			sqrt(sphere->radius2) : sqrt(cylinder->radius2);
		nk_property_float(g_nk_context, "#radius:", 0.0f, &radius,
			INFINITY, 1.0f, 1.0f);
		nk_tree_pop(g_nk_context);
	}
}

void	display_corresponding_options(const t_primitive *prim)
{
	const t_byte *actual;
	static float angle;
	const t_cone *cone;

	actual = primitive_get_actual(prim);
	if (prim->primitive_type == SPHERE || prim->primitive_type == CYLINDER)
		show_sphere_cylinder_options(actual, prim->primitive_type);
	else if (prim->primitive_type == CONE)
	{
		cone = (const t_cone*)actual;
		if (nk_tree_push(g_nk_context, NK_TREE_TAB, "Cone", NK_MAXIMIZED))
		{
			nk_layout_row_dynamic(g_nk_context, 30, 1);
			angle = (180.0 / M_PI) * acos(sqrt(cone->cos2angle));
			nk_property_float(g_nk_context, "#angle:", 0.0f,
				&angle, 180.0f, 1.0f, 1.0f);
			nk_tree_pop(g_nk_context);
		}
	}
	else
	{
		// other shapes action
	}
}

int		display_shapes_tree(const t_shape *shape,
	const t_primitive *primitive, int i)
{
	if (nk_tree_push_id(g_nk_context, NK_TREE_NODE,
		g_primitive_names[primitive->primitive_type - 1], NK_MINIMIZED, i++))
	{
		if (nk_button_label(g_nk_context, "Select"))
		{
			select_object(shape->addr);
		}
		if (nk_tree_push_id(g_nk_context, NK_TREE_NODE, "Expand Me",
			NK_MINIMIZED, i++))
		{
			if (nk_button_label(g_nk_context, "Select"))
			{
				ft_printf("%i\n", shape->addr);
			}
			nk_tree_pop(g_nk_context);
		}
		nk_tree_pop(g_nk_context);
	}
	return (i);
}

void	display_shapes_win(void)
{
	int					i;
	const t_shape		*shape;
	const t_primitive	*primitive;
	t_iterator			iter;

	if (nk_begin(g_nk_context, "Scene tree", nk_rect(TREE_X, TREE_Y, TREE_WIDTH,
		TREE_HEIGHT), NK_WINDOW_BORDER | NK_WINDOW_TITLE))
	{
		iter = shape_begin(&g_main_scene);
		i = 0;
		while (has_next(&iter))
		{
			shape = shape_next(&iter);
			primitive = shape_get_primitive(shape);
			i = display_shapes_tree(shape, primitive, i);
		}
	}
	nk_end(g_nk_context);
}
