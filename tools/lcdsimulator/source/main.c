#include <SDL2/SDL.h>
#include "common.h"
#include "graphics/pixelbuffer.h"
#include "graphics/renderer.h"

// Constant screen size
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const  char * WINDOW_NAME = "Simulation?";


//  Global
bool running = false;
SDL_Window * window = NULL;
SDL_Renderer * renderer = NULL;

G_PixelBuffer * buffer;


// Test values, just for fun, TODO: create a drawing library.
int esh = 64;
int esw = 128;


int init(){
	
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("You should fix this soon, ERROR: %s\n", SDL_GetError());
		return 1;
	}
	
	window = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(window == NULL){
		printf("Could not create the desired SDL_Window, :-(, ERROR: %s\n", SDL_GetError());	
		return 1;
	}

	
	renderer = SDL_CreateRenderer(window,  0, SDL_RENDERER_PRESENTVSYNC);
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);


	if(renderer == NULL){
		printf("Is this a computer or a toaster?, mmm, ERROR: %s\n", SDL_GetError());	
		return 1;
	}

	buffer = g_create_buffer(128, 64);

	g_set_pixel(buffer, 2, 0, 1);

	g_clear(buffer);

	g_set_pixel(buffer, 4, 0, 1);

	vec2 x1 = {5, 10}, x2 = {20, 30};
	g_draw_line(buffer, x1, x2, 1);
	g_draw_line(buffer, vec2_sum(x1, x2), x1, 1);
	g_draw_rect(buffer, vec2_create(0,0), vec2_create(40,50), 1);
	return 0;
}

void clear(int r, int g, int b, int a){

	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderClear(renderer);

}

//Crappy values for now URGENT TODO update this.

int padding = 1; // Pixels
int pixel_size = 3;

void render(){

	clear(0x22, 0x22, 0x22, 0xff);

	for(int y = 0; y < esh; y++){
		for(int x = 0; x < esw; x++){
			int e = g_get_pixel(buffer, x, y);

			if(e == 0){
				SDL_SetRenderDrawColor(renderer, 0x00, 0x3F, 0x00, 0xFF);
			}else{
				SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
			}

			SDL_Rect pixelrect = {65+(pixel_size+padding)*x, 20+(pixel_size+padding)*y, pixel_size, pixel_size};
			SDL_RenderFillRect(renderer, &pixelrect);
		}
	}

	//Update renderer
	SDL_RenderPresent(renderer);
}

void enter_main_loop(){

	running = true;
	
	SDL_Event e;

	while(running){

		while(SDL_PollEvent(&e) != 0){
			if(e.type == SDL_QUIT){
				running = false;
				
			}
		}

		render();

	}

}

void quit(){

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

}

int main(int argc, char* args[]){

	init();

	enter_main_loop();

	quit();

	return 0;
}