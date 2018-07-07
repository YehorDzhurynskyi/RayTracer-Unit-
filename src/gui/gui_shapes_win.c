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

static const char *g_primitive_names[] = {"Composite", "Point", "Plane", "Sphere", "Cone", "Cylinder"};

void display_shapes_win(void)
{
	int i;

	if (nk_begin(g_nk_context, "Scene tree", nk_rect(TREE_X, TREE_Y, TREE_WIDTH, TREE_HEIGHT), NK_WINDOW_BORDER | NK_WINDOW_TITLE))
	{
		t_iterator iter = shape_begin(&g_main_scene);
		i = 0;
		while (has_next(&iter))
		{
			const t_shape *shape = shape_next(&iter);
			const t_primitive *primitive = shape_get_primitive(shape);
			if (nk_tree_push_id(g_nk_context, NK_TREE_NODE,
								g_primitive_names[primitive->primitive_type - 1], NK_MINIMIZED, i++))
			{
				if (nk_button_label(g_nk_context, "Select"))
				{
					select_object(shape->addr);
				}
				if (nk_tree_push_id(g_nk_context, NK_TREE_NODE, "Expand Me", NK_MINIMIZED, i++))
				{
					if (nk_button_label(g_nk_context, "Select"))
					{
						ft_printf("%i\n", shape->addr);
					}
					nk_tree_pop(g_nk_context);
				}
				nk_tree_pop(g_nk_context);
			}
		}
	}
	nk_end(g_nk_context);
	/*
    // static int active1 = 0;
    static int active2 = 0;
    static int active3 = 0;
    // static int active4 = 0;
    struct nk_rect rect = nk_rect(10, 10, 600, 300);
    if (nk_begin(g_nk_context, "Bug Demo", rect, NK_WINDOW_MOVABLE | NK_WINDOW_BORDER | NK_WINDOW_TITLE | NK_WINDOW_CLOSABLE))
    {
        int id = 0;
        struct nk_rect w;
        if (nk_tree_push_id(g_nk_context, NK_TREE_NODE, "Children", NK_MAXIMIZED, id++))
        {
            if (nk_tree_push_id(g_nk_context, NK_TREE_NODE, "Expand Me", NK_MINIMIZED, id++))
            {
                w = nk_layout_widget_bounds(g_nk_context);
                nk_layout_row_begin(g_nk_context, NK_STATIC, 18, 2);
                nk_layout_row_push(g_nk_context, 24);

                nk_button_label(g_nk_context, "...");
                nk_layout_row_push(g_nk_context, w.w - 24);

                nk_selectable_label(g_nk_context, "Hello", NK_TEXT_ALIGN_LEFT, &active2);
                nk_layout_row_end(g_nk_context);
                nk_tree_pop(g_nk_context);
            }
            w = nk_layout_widget_bounds(g_nk_context);
            nk_layout_row_begin(g_nk_context, NK_STATIC, 18, 2);
            nk_layout_row_push(g_nk_context, 24);

            nk_button_label(g_nk_context, "...");
            nk_layout_row_push(g_nk_context, w.w - 24);

            nk_selectable_label(g_nk_context, "I will disappear.", NK_TEXT_ALIGN_LEFT, &active3);
            nk_layout_row_end(g_nk_context);
            nk_tree_pop(g_nk_context);
        }
    }
    nk_end(g_nk_context);


                nk_layout_row_static(g_nk_context, 5, 30, 1);
                // nk_layout_row_dynamic(g_nk_context, 1, 1);
                struct nk_rect bounds = nk_widget_bounds(g_nk_context);

                if (nk_contextual_begin(g_nk_context, 0, nk_vec2(100, 300), bounds))
                {
                    nk_layout_row_dynamic(g_nk_context, 25, 1);
                    nk_label(g_nk_context, "Right click me for menu", NK_TEXT_LEFT);
                    // nk_checkbox_label(ctx, "Menu", &show_menu);
                    ft_printf("HELLO\n", shape->addr);
                    nk_contextual_end(g_nk_context);
                }


    */
}