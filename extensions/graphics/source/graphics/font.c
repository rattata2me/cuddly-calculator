#include "graphics/font.h"

unsigned char FONT_SIZE = 16;  

void g_draw_text(G_Surface * canvas, G_Surface * bitmap, char * text, vec2 pos){
	int i = 0;
	while(text[i] != '\0'){
		g_draw_word(canvas, bitmap, text[i], vec2_create(pos.x+bitmap->width/FONT_SIZE*i, pos.y));
		i++;
	}
}

void g_draw_word(G_Surface * canvas, G_Surface * bitmap, char letter, vec2 pos){
	vec2 size = {bitmap->width/FONT_SIZE, bitmap->height/FONT_SIZE};
	for(int y = 0; y < size.y; y++){
		for(int x = 0; x < size.x; x++){
			int p = g_get_pixel(bitmap, (letter%FONT_SIZE)*size.x + x, y+size.y*(letter/FONT_SIZE));
			if(p == 1){
				g_set_pixel(canvas, pos.x+x, pos.y+y, p);
			}
		}
	}
}
