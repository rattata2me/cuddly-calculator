#include "ncurses_window.h"

void ncurses_init(){

	initscr();
	noecho();

}


void ncurses_loop(G_Surface * buffer){
	char cBlock = (char)0x2588;
	erase();
	for(int y = 0; y < buffer->height; y++){
		for(int x = 0; x < buffer->width; x++){
			int e = g_get_pixel(buffer, x, y);
			if(e == 0){
				addch(0x20);
			}else{
				addch(cBlock);
			}
		}
		printw("\n");
	}
	refresh();	
}