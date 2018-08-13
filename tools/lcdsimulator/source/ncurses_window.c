#include "ncurses_window.h"
#include "unistd.h"

#define BLACK       1
#define WHITE  2

void ncurses_init(){

	initscr();
	noecho();
	start_color();
	init_pair(BLACK, COLOR_BLACK, COLOR_WHITE);
	init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);
}


void ncurses_loop(G_Scene * scene){
	int cBlock = 0x20;
	erase();
	for(int y = 0; y < scene->buffer->height+1; y++){
		for(int x = 0; x < scene->buffer->width+1; x++){
			int e = g_get_pixel(scene->buffer, x-1, y-1);
			if(x == 0 || y == 0 || x == scene->buffer->width || y == scene->buffer->height){
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
	usleep(20000);
}

void ncurses_input(G_Scene * scene){
	nodelay(stdscr, TRUE);
	int val = getch();
	int val2 = getch();
	int val3 = getch();
	if(val2 != ERR || val3 != ERR){
		int comp = val+(val2<<8)+(val3<<8);
		switch(comp){
			case 39963: //Up
				val = I_UP;
				break;
			case 40219: //Down
				val = I_DOWN;
				break;
			case 40731:  //Right
				val = I_RIGHT;
				break;
			case 40475: //Left
				val = I_LEFT;
				break;
		}
	}
	
	// REMAP
	if(val == 10) val = I_ENTER; // NewLine to Enter

	if(val != ERR) input_set_key(scene->input_buffer, val, 1);
}
