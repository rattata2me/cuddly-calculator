#include "sdl_window.h"

const  char * WINDOW_NAME = "Simulation?";

// Constant screen size
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Crappy values for now URGENT TODO update this.

int padding = 0; // Pixels
int pixel_size = 4;

void sdl_clear(sdl_window * window, int r, int g, int b, int a){

	SDL_SetRenderDrawColor(window->renderer, r, g, b, a);
	SDL_RenderClear(window->renderer);

}


sdl_window * sdl_init_window(){

	sdl_window * window = malloc(sizeof(sdl_window));

	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("You should fix this soon, ERROR: %s\n", SDL_GetError());
		return NULL;
	}

	window->window = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(window->window == NULL){
		printf("Could not create the desired SDL_Window, :-(, ERROR: %s\n", SDL_GetError());
		return NULL;
	}


	window->renderer = SDL_CreateRenderer(window->window,  0, SDL_RENDERER_PRESENTVSYNC);
	SDL_RenderSetLogicalSize(window->renderer, SCREEN_WIDTH, SCREEN_HEIGHT);


	if(window->renderer == NULL){
		printf("Is this a computer or a toaster?, mmm, ERROR: %s\n", SDL_GetError());
		return NULL;
	}

	return window;
}

void sdl_render(sdl_window * window, G_Scene * scene){

	sdl_clear(window, 0x22, 0x22, 0x22, 0xff);

	for(int y = 0; y < scene->buffer->height; y++){
		for(int x = 0; x < scene->buffer->width; x++){
			int e = g_get_pixel(scene->buffer, x, y);

			if(e == 0){
				SDL_SetRenderDrawColor(window->renderer, 0x00, 0x3F, 0x00, 0xFF);
			}else{
				SDL_SetRenderDrawColor(window->renderer, 0x00, 0xFF, 0x00, 0xFF);
			}

			SDL_Rect pixelrect = {65+(pixel_size+padding)*x, 20+(pixel_size+padding)*y, pixel_size, pixel_size};
			SDL_RenderFillRect(window->renderer, &pixelrect);
		}
	}

	//Update renderer
	SDL_RenderPresent(window->renderer);
}

void sdl_quit(sdl_window * window){

	SDL_DestroyRenderer(window->renderer);
	SDL_DestroyWindow(window->window);
	SDL_Quit();
	free(window);

}

SDL_Event e;

bool sdl_loop(sdl_window * window, G_Scene * scene){

	bool running = true;
	SDL_StartTextInput();
	while(SDL_PollEvent(&e) != 0){
			switch(e.type){

				case SDL_QUIT:
					running = false;
					break;

				case SDL_TEXTINPUT:
					input_set_key(scene->input_buffer, e.text.text[0], 1);
					break;
				case SDL_KEYDOWN:;
					int key = e.key.keysym.sym;
					int t = 0;
					switch (key){
						case SDLK_RETURN: // ENTER
							t = I_ENTER;
							break;
						case 8: // DEL Key
							t = I_DEL;
							break;
						case 9: // RETURN (tab)
							t = I_RETURN;
							break;
						case 27: // ESC
							t = I_MENU;
							break;
						case SDLK_UP:
							t = I_UP;
							break;
						case SDLK_DOWN:
							t = I_DOWN;
							break;
						case SDLK_LEFT:
							t = I_LEFT;
							break;
						case SDLK_RIGHT:
							t = I_RIGHT;
							break;
					}
					if(t != 0) input_set_key(scene->input_buffer, t, 1);
					break;
			}
		}

	if(scene->need_update){
		sdl_render(window, scene);
		scene->need_update = 0;
	}
	return running;

}
