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

char *testbuf[] = {"Point", "Plane", "Sphere", "Cone", "Cylinder"};

static int shapesnum = 5;

typedef enum {
    COMPOSITE = 0,
    POINT,
    PLANE,
    SPHERE,
    CONE,
    CYLINDER
} t_primitive_type;

typedef struct __attribute__((packed))
{
    // t_claddress			material_addr;
    // cl_int				nchildren;
    t_primitive_type primitive_type;
    // t_relation_type		relation_type; // show combo box
} t_shape_ex;

void display_shapes_win(void)
{
    int i;

    t_shape_ex example[5];
    example[0].primitive_type = 2;
    example[1].primitive_type = 6;
    example[2].primitive_type = 3;
    example[3].primitive_type = 4;
    example[4].primitive_type = 5;
    i = 0;
    if (nk_begin(g_nk_context, "Scene's Shapes", nk_rect(10, 550, 220, 345),
                 NK_WINDOW_BORDER | NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
    {
        while (i < shapesnum)
        {
            if (nk_tree_push_id(g_nk_context, NK_TREE_TAB,
                                testbuf[example[i].primitive_type - 2], NK_MINIMIZED, i))
            {
                nk_tree_pop(g_nk_context);
            }
            i++;
        }
    }
    nk_end(g_nk_context);
}