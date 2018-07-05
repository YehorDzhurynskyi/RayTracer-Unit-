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
#include "sceneiterator.h"

extern struct nk_context *g_nk_context;

char *testbuf[] = {"Composite", "Point", "Plane", "Sphere", "Cone", "Cylinder"};

void display_shapes_win(void)
{
    int i;

    if (nk_begin(g_nk_context, "Scene's Shapes", nk_rect(10, 550, 220, 345),
                 NK_WINDOW_BORDER | NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
    {
        if (g_main_scene != NULL)
        {
            t_iterator iter = shape_begin(g_main_scene);
            i = 0;
            while (has_next(&iter))
            {
                const t_shape *shape = shape_next(&iter);
                const t_primitive *primitive = shape_get_primitive(shape);
                if (nk_tree_push_id(g_nk_context, NK_TREE_TAB,
                                    testbuf[primitive->primitive_type - 1], NK_MINIMIZED, i))
                {
                    nk_tree_pop(g_nk_context);
                }
                i++;
            }
        }
    }
    nk_end(g_nk_context);
}