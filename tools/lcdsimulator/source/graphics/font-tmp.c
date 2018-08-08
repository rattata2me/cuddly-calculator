#include "graphics/font.h"

G_Font * g_create_font_from_data(unsigned int width, unsigned int height, 
		unsigned char * indices, unsigned char * pixels, unsigned int size){
	
	int nrow = (width+(G_MEMORY_UNIT - (width % G_MEMORY_UNIT)))/G_MEMORY_UNIT;

	G_Surface * chars = malloc(sizeof(G_Surface)*size);
	for(int i = 0; i < size; i++){
		(chars+i)->width = width;
		(chars+i)->height = height;
		(chars+i)->striplen = nrow;
		(chars+i)->pixels = pixels+(nrow*height*i);
	}

	G_Font * font = malloc(sizeof(G_Font));
	font->char_size = nrow*height;
	font->chars = chars;
	font->size = size;
	font->indices = indices;

	return font;


}

void g_draw_text(G_Surface * surface, G_Font * font, char * msg, 
		unsigned int size, vec2 pos){

	for(int i = 0; i < size; i++){
		for(int j = 0; j < font->size; j++){
			if(font->indices[j] == msg[i]){
				g_draw_alpha_over(surface, font->chars+j,
						vec2_add(pos, (font->chars->width-6)*i, 0), 1);	
			}
		}
	}
	
}

