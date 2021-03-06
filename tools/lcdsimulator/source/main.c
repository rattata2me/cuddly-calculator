#include "common.h"

#include "graphics/pixelsurface.h"
#include "graphics/renderer.h"
#include "graphics/texture.h"
#include "logo.h"
#include "graphics/font.h"
#include "bigfont.h"
#include "smallfont.h"
#include "graphics/ui.h"
#include "programs/calc.h"
#include "programs/graph.h"
#include "programs/menu.h"

#ifdef SDL_SIM
	#include "sdl_window.h"
#endif

#ifdef NCURSES_SIM
	#include "ncurses_window.h"
	G_Surface * input_buffer;
#endif

//  Global
bool running = false;

#ifdef SDL_SIM
	sdl_window * window;
#endif

G_Surface * buffer;

// Test values, just for fun
int esh = 64;
int esw = 128;

G_Scene * program;

void init_program(){
	switch(program->programid){
		case 0:
			menu_init(program);
			break;
		case 1:
			calc_init(program);
			break;
		case 2:
			graph_init(program);
			break;
		default:
			menu_init(program);
			break;
	}
}

void draw_program(){
	switch(program->programid){
		case 0:
			menu_draw(program);
			break;
		case 1:
			calc_draw(program);
			break;
		case 2:
			graph_draw(program);
			break;
		default:
			menu_draw(program);
			break;
	}
}

int init(){

	#ifdef SDL_SIM
		window = sdl_init_window();
		if(window == NULL){
			return 1;
		}
	#endif

	#ifdef NCURSES_SIM
		ncurses_init();
		input_buffer = input_create_buffer();
	#endif

	program = malloc(sizeof(G_Scene));

	buffer = g_create_surface(128, 64);



	program->need_update = 0;
	program->buffer = buffer;

	program->programid = PROGRAM_MENU;

	return 0;
}

char lastprogramid = -1;
void render(){
	if(lastprogramid != program->programid){
		init_program();
		lastprogramid = program->programid;
	}
	draw_program();

}

void enter_main_loop(){

	running = true;

	while(running){

		#ifdef SDL_SIM
			running = sdl_loop(window, program);
		#endif

		#ifdef NCURSES_SIM
			ncurses_loop(program);
			ncurses_input(program);
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
