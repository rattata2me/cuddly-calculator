#include "ncurses_window.h"


#define BLACK       1
#define WHITE  2

void ncurses_init(){

	initscr();
	noecho();
	start_color();
	init_pair(BLACK, COLOR_BLACK, COLOR_WHITE);
	init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);
}


void ncurses_loop(G_Surface * buffer){
	int cBlock = 0x20;
	erase();
	for(int y = 0; y < buffer->height+2; y++){
		for(int x = 0; x < buffer->width+2; x++){
			int e = g_get_pixel(buffer, x-1, y-1);
			if(x == 0 || y == 0 || x == buffer->width+1 || y == buffer->height+1){
				addch(98);
				if(!(x % 3 == 0)) addch(98);
			}else{
				if(e == 0){
					addch(0x20);
					if(!(x % 3 == 0)) addch(0x20);
				}else{
					attrset(COLOR_PAIR(BLACK));
					addch(cBlock);
					if(!(x % 3 == 0)) addch(cBlock);
					attrset(COLOR_PAIR(WHITE));
				}
			}
		}
		printw("\n");
	}
	refresh();	
}

