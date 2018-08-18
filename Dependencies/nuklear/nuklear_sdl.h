/*
 * Nuklear - 1.32.0 - public domain
 * no warrenty implied; use at your own risk.
 * authored from 2015-2017 by Micha Mettke
 */
/*
 * ==============================================================
 *
 *                              API
 *
 * ===============================================================
 */
#ifndef NK_SDL_GL2_H_
#define NK_SDL_GL2_H_

#include <SDL.h>
#include <SDL_opengl.h>
#include "src/nuklear.h"

NK_API struct nk_context*   nk_sdl_init(SDL_Window *win);
NK_API void                 nk_sdl_font_stash_begin(struct nk_font_atlas **atlas);
NK_API void                 nk_sdl_font_stash_end(void);
NK_API int                  nk_sdl_handle_event(SDL_Event *evt);
NK_API void                 nk_sdl_render(enum nk_anti_aliasing);
NK_API void                 nk_sdl_shutdown(void);

extern const struct nk_rect nk_null_rect;
extern const struct nk_color nk_red;
extern const struct nk_color nk_green;
extern const struct nk_color nk_blue;
extern const struct nk_color nk_white;
extern const struct nk_color nk_black;
extern const struct nk_color nk_yellow;

#endif
