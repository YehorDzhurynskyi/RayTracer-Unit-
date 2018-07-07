/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_object_win.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 13:59:40 by pzubar            #+#    #+#             */
/*   Updated: 2018/07/05 13:59:42 by pzubar           ###   ########.fr       */
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
static const t_shape *g_selected_shape = NULL;

void select_object(t_claddress addr)
{
	g_main_scene.config.selected_shape_addr = addr;
	g_selected_shape = (const t_shape *)(g_main_scene.host_shapebuffer + addr);
}

static void distplay_shape_position(const t_primitive *primitive)
{
	static float xpos;
	static float ypos;
	static float zpos;

	xpos = primitive->position.x;
	ypos = primitive->position.y;
	zpos = primitive->position.z;

	nk_layout_row_dynamic(g_nk_context, 30, 1);
	nk_label(g_nk_context, "position", NK_TEXT_LEFT);
	nk_property_float(g_nk_context, "#x:", -INFINITY, &xpos, INFINITY, 1.0f, 1.0f);
	nk_property_float(g_nk_context, "#y:", -INFINITY, &ypos, INFINITY, 1.0f, 1.0f);
	nk_property_float(g_nk_context, "#z:", -INFINITY, &zpos, INFINITY, 1.0f, 1.0f);
}

static void distplay_shape_orientation(const t_primitive *primitive)
{
	static float rx;
	static float ry;
	static float rz;

	rx = atan2(primitive->orientation.s9, primitive->orientation.sa) * (180.0f / M_PI);
	const float a = sqrt(primitive->orientation.s9 * primitive->orientation.s9 + primitive->orientation.sa * primitive->orientation.sa);
	ry = atan2(-primitive->orientation.s8, a) * (180.0f / M_PI);
	rz = atan2(-primitive->orientation.s4, primitive->orientation.s0) * (180.0f / M_PI);

	nk_layout_row_dynamic(g_nk_context, 30, 1);
	nk_label(g_nk_context, "orientation", NK_TEXT_LEFT);
	nk_property_float(g_nk_context, "#rotX:", -180.0f, &rx, 180.0f, 1.0f, 1.0f);
	nk_property_float(g_nk_context, "#rotY:", -180.0f, &ry, 180.0f, 1.0f, 1.0f);
	nk_property_float(g_nk_context, "#rotZ:", -180.0f, &rz, 180.0f, 1.0f, 1.0f);
}

void display_object_win()
{
	static int current_mode = 0;
	const t_primitive *prim;
	const t_byte *actual;

	if (nk_begin(g_nk_context, "Object", nk_rect(OBJ_X, OBJ_Y, OBJ_WIDTH, OBJ_HEIGHT),
				NK_WINDOW_BORDER | NK_WINDOW_TITLE))
	{
		if (g_selected_shape != NULL)
		{
			if (nk_tree_push(g_nk_context, NK_TREE_TAB, "Shape", NK_MAXIMIZED))
			{
				static const char *weapons[] = {"UNION", "INTERSECTION", "NEGATION"};
				nk_layout_row_dynamic(g_nk_context, 30, 1);
				nk_label(g_nk_context, "relation type", NK_TEXT_LEFT);
				current_mode = nk_combo(g_nk_context, weapons, 3, current_mode, 30, nk_vec2(190, 200));
				if (nk_button_label(g_nk_context, "Select material"))
					ft_printf("Material was selected\n");
				nk_tree_pop(g_nk_context);
			}
			prim = shape_get_primitive(g_selected_shape);
			if (nk_tree_push(g_nk_context, NK_TREE_TAB, "Primitive", NK_MAXIMIZED))
			{
				distplay_shape_position(prim);
				distplay_shape_orientation(prim);
				nk_tree_pop(g_nk_context);
			}
			// ft_printf("primitive_type: %i\n", prim->primitive_type);
			actual = primitive_get_actual(prim);

			//Give me a method to modify i
			if (prim->primitive_type == SPHERE)
			{
				const t_sphere *sphere = (const t_sphere*)actual;
				if (nk_tree_push(g_nk_context, NK_TREE_TAB, "Sphere", NK_MAXIMIZED))
				{
					nk_layout_row_dynamic(g_nk_context, 30, 1);
					static float radius;
					radius = sqrt(sphere->radius2);
					nk_property_float(g_nk_context, "#radius:", 0.0f, &radius, INFINITY, 1.0f, 1.0f);
					nk_tree_pop(g_nk_context);
				}
			}
			else if (prim->primitive_type == CYLINDER)
			{
				const t_cylinder *cylinder = (const t_cylinder*)actual;
				if (nk_tree_push(g_nk_context, NK_TREE_TAB, "Cylinder", NK_MAXIMIZED))
				{
					nk_layout_row_dynamic(g_nk_context, 30, 1);
					static float radius;
					radius = sqrt(cylinder->radius2);
					nk_property_float(g_nk_context, "#radius:", 0.0f, &radius, INFINITY, 1.0f, 1.0f);
					nk_tree_pop(g_nk_context);
				}
			}
			else if (prim->primitive_type == CONE)
			{
				const t_cone *cone = (const t_cone*)actual;
				if (nk_tree_push(g_nk_context, NK_TREE_TAB, "Cone", NK_MAXIMIZED))
				{
					nk_layout_row_dynamic(g_nk_context, 30, 1);
					static float angle;
					angle = (180.0 / M_PI) * acos(sqrt(cone->cos2angle));
					nk_property_float(g_nk_context, "#angle:", 0.0f, &angle, 180.0f, 1.0f, 1.0f);
					nk_tree_pop(g_nk_context);
				}
			}
			else
			{
				// ft_printf("Another shape (WTF?!) %i\n", prim->primitive_type);
			}
		}
		else
		{
			nk_layout_row_dynamic(g_nk_context, 100, 1);
			nk_label(g_nk_context, "OBJECT IS NOT SELECTED", NK_TEXT_CENTERED);
		}
		// shape:
		// print relation type combo box
		// print material addr button

		// primitive
		// print position vec3
		// print orientation vec3
		// const t_primitive *prim = shape_get_primitive(g_selected_shape);
		// const t_byte *actual = primitive_get_actual(prim);
		/*
        if (prim->primitive_type == SPHERE)
        {
            // const t_sphere *sphere = (const t_sphere*)actual;
            // print sqrt(sphere->radius2)
        }
        else if (prim->primitive_type == CYLINDER)
        {
            // const t_cylinder *cylinder = (const t_cylinder*)actual;
            // print sqrt(cylinder->radius2)
        }
        else if (prim->primitive_type == CONE)
        {
            // const t_cone *cone = (const t_cone*)actual;
            // print sqrt(cone->radius2)
        }
        */
	}
	nk_end(g_nk_context);
}
