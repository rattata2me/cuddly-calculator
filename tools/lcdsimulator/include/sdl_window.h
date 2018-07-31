#ifndef CCALCLCDSIM_SRC_SDL_WINDOW_H_
#define CCALCLCDSIM_SRC_SDL_WINDOW_H_

#include <SDL2/SDL.h>

#include "graphics/pixelsurface.h"

typedef struct{

	SDL_Window * window;
	SDL_Renderer * renderer;

} sdl_window;

void sdl_clear(sdl_window * window, int r, int g, int b, int a);

sdl_window * sdl_init_window();

void sdl_render(sdl_window * window, G_Surface * buffer);

void sdl_quit(sdl_window * window);

bool sdl_loop(sdl_window * window, G_Surface * buffer);

#endif