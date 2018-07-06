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

void set_object(t_claddress addr)
{
	// if (g_selected_shape != NULL || addr == g_selected_shape->addr)
	//     return ;
	ft_printf("addr: %i\n", addr);
	void *add = g_main_scene.host_shapebuffer + addr;
	g_selected_shape = (const t_shape *)add;
}

void distplay_shape_position(float posx, float posy, float posz)
{
	static float xpos;
	static float ypos;
	static float zpos;

	xpos = posx;
	ypos = posy;
	zpos = posz;

	nk_layout_row_dynamic(g_nk_context, 30, 1);
	nk_label(g_nk_context, "Positioning:", NK_TEXT_LEFT);
	nk_property_float(g_nk_context, "#X:", 0, &xpos, 64.0f, 0.1f, 0.2f);
	nk_property_float(g_nk_context, "#Y:", 0, &ypos, 64.0f, 0.1f, 0.2f);
	nk_property_float(g_nk_context, "#Z:", 0, &zpos, 64.0f, 0.1f, 0.2f);
}

void display_object_win()
{
	static int current_weapon = 0;
	const t_primitive *prim;
	const t_byte *actual;

	// float x_pos;

	if (nk_begin(g_nk_context, "Object", nk_rect(X_CENTERED + 825, 5, 300, 545),
				 NK_WINDOW_BORDER | NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
	{
		if (g_selected_shape)
		{
			prim = shape_get_primitive(g_selected_shape);
			// ft_printf("primitive_type: %i\n", prim->primitive_type);
			actual = primitive_get_actual(prim);

			//Give me a method to modify i
			distplay_shape_position(prim->position.x, prim->position.y, prim->position.z);
			if (prim->primitive_type == SPHERE)
			{
				// ft_printf("Sphere\n");
				// ft_printf("Sphere\n");
				// const t_sphere *sphere = (const t_sphere*)actual;
				// ft_printf("%f\n", sqrt(sphere->radius2));
			}
			else if (prim->primitive_type == CYLINDER)
			{
				// ft_printf("Cylinder\n");
				// const t_cylinder *cylinder = (const t_cylinder*)actual;
				// print sqrt(cylinder->radius2)
			}
			else if (prim->primitive_type == CONE)
			{
				// ft_printf("CONE\n");
				// const t_cylinder *cylinder = (const t_cylinder*)actual;
				// print sqrt(cylinder->radius2)
			}
			else if (prim->primitive_type == PLANE)
			{
				// ft_printf("PLANE\n");
				// const t_cylinder *cylinder = (const t_cylinder*)actual;
				// print sqrt(cylinder->radius2)
			}
			else if (prim->primitive_type == COMPOSITE)
			{
				// ft_printf("COMPOSITE\n");
				// const t_cylinder *cylinder = (const t_cylinder*)actual;
				// print sqrt(cylinder->radius2)
			}
			else
			{
				// ft_printf("Another shape (WTF?!) %i\n", prim->primitive_type);
			}
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
		static const char *weapons[] = {"Fist", "Pistol", "Shotgun", "Plasma", "BFG"};
		nk_layout_row_dynamic(g_nk_context, 30, 1);
		nk_label(g_nk_context, "Select relation type:", NK_TEXT_LEFT);
		current_weapon = nk_combo(g_nk_context, weapons, 5, current_weapon, 25, nk_vec2(190, 200));
	}
	nk_end(g_nk_context);
}
