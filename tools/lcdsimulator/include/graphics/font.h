#ifndef CCALCLC_SRC_GRAPHICS_FONT_H_
#define CCALCLC_SRC_GRAPHICS_FONT_H_

#include "graphics/texture.h"

typedef struct{
	
	G_Surface * chars;
	unsigned int char_size;
	unsigned char * indices;
	unsigned int size;

}G_Font;

G_Font * g_create_font_from_data(unsigned int width, unsigned int height, 
		unsigned char * indices, unsigned char * pixels, unsigned int size);

void g_draw_text(G_Surface * surface, G_Font * font, char * msg,                                     unsigned int size, vec2 pos);

#endif

