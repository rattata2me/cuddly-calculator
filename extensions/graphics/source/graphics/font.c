#include "graphics/font.h"

unsigned char FONT_SIZE = 16;  

void g_draw_text(G_Surface * canvas, G_Surface * bitmap, 
		char * text, vec2 pos){
	vec2 size = {bitmap->width/FONT_SIZE, bitmap->height/FONT_SIZE};
	int i = 0;
	while(text[i] != '\0'){
		for(int y = 0; y < size.y; y++){
			for(int x = 0; x < size.x; x++){
				int p = g_get_pixel(bitmap, (text[i]%FONT_SIZE)*size.x + x, y+size.y*(text[i]/FONT_SIZE));
				if(p == 1){
					g_set_pixel(canvas, x+pos.x+size.x*i, y+pos.y, p);
				}
			}
		}
		i++;
	}
}
