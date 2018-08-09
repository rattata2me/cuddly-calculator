#include "common.h"

#include "graphics/pixelsurface.h"
#include "graphics/renderer.h"
#include "graphics/texture.h"
#include "logo.h"
#include "graphics/font.h"
#include "bigfont.h"
#include "smallfont.h"

#ifdef SDL_SIM
	#include "sdl_window.h"
#endif

#ifdef NCURSES_SIM
	#include "ncurses_window.h"
#endif

//  Global
bool running = false;

#ifdef SDL_SIM
	sdl_window * window;
#endif

G_Surface * buffer, * texture, * s, * b, * c;


// Test values, just for fun
int esh = 64;
int esw = 128;


int init(){
	
	#ifdef SDL_SIM
		window = sdl_init_window();
		if(window == NULL){ 
			return 1;
		}
	#endif

	#ifdef NCURSES_SIM
		ncurses_init();
	#endif

		

	buffer = g_create_surface(128, 64);
	texture = g_create_surface_from_pixels(logo_width, logo_height, logo_pixels);
	b = g_create_surface_from_pixels(bigfont_width, bigfont_height, bigfont_pixels);
	s = g_create_surface_from_pixels(smallfont_width, smallfont_height, smallfont_pixels);
	return 0;
}

int k = 0;
void render(){


	g_clear(buffer);
	g_draw_text(buffer, b, "1. Big Font", vec2_create(1,10));
	g_draw_text(buffer, s, "2. Small Font", vec2_create(2, 40));
	//g_draw_text(buffer, font, "holAC MunD0", 11, vec2_create(10, 10));
	//g_draw_surface(buffer, b, vec2_create(5+16, 10));
	//g_draw_surface(buffer, c, vec2_create(16*2, 10));
	//g_draw_surface(buffer, texture, vec2_create(-1,-5));
	//g_draw_rect(buffer, vec2_create(k/10,1), vec2_create(10,10), 1);
	//g_draw_rect(buffer, vec2_create(100-k/5,20), vec2_create(10,10), 1);
	//g_fill_shape(buffer, vec2_create(12, 13), 1U);
	//g_fill_shape(buffer, vec2_create(12, 13), 0U);
	k++;

}

void enter_main_loop(){

	running = true;
	
	while(running){
		
		#ifdef SDL_SIM
			running = sdl_loop(window, buffer);
		#endif

		#ifdef NCURSES_SIM
			ncurses_loop(buffer);
		#endif 
		render();
	}

}

void quit(){

	#ifdef SDL_SIM
		sdl_quit(window);
	#endif

}

int main(int argc, char* args[]){

	if(init()){ 
		return 0;
	}

	enter_main_loop();

	quit();

	return 0;
}

