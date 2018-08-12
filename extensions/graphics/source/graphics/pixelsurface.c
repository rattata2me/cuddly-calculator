#include "graphics/pixelsurface.h"

int G_MEMORY_UNIT = sizeof(unsigned char)*8;


G_Surface * g_create_surface(unsigned int width, unsigned int height){

	G_Surface * surface;

	width += -1;
	// Divide the pixel array in int groups. One pixel = one bit, so there are sizeof(int) pixels in each group.
	int nrow = (width+(G_MEMORY_UNIT - (width % G_MEMORY_UNIT)))/G_MEMORY_UNIT;

	// Buffer allocation
	surface = malloc(sizeof(G_Surface));
	surface->width = width;
	surface->striplen = nrow;
	surface->height = height;
	surface->pixels = (unsigned char *) calloc(nrow*height, (G_MEMORY_UNIT/8));

	return surface;
}

void g_destroy_surface(G_Surface * surface){

	free(surface->pixels);
	free(surface);

}

void g_set_pixel(G_Surface * surface, int x, int y, int val){

	// Box limitation to prevent overflow.
	if(((x < 0) | (x >= surface->width)) | ((y < 0) | (y >= surface->height))) return;

	//Relative x position in the memory block
	int rest = x%G_MEMORY_UNIT;

	// Memory block position
	int xpos = (x - rest) / G_MEMORY_UNIT;

	// Memory block pointer
	unsigned char * gval = (unsigned char *)((surface->pixels)+xpos+y*(surface->striplen));
	
	if(val == 0){
		
		// Bit substraction
		unsigned char sum = ~(1U << ((G_MEMORY_UNIT-1) - rest));
		sum = (*gval) & sum;
		*gval = sum;

	}else{
	
		// Bit addition
		unsigned char sum = 1U << ((G_MEMORY_UNIT-1) - rest);
		sum = (*gval) | sum;
		*gval = sum;

	}
}

int g_get_pixel(G_Surface * surface, int x, int y){

	// Box limitation to prevent overflow.
	if(((x < 0) | (x >= surface->width)) | ((y < 0) | (y >= surface->height))) return 0;

	//Relative x position in the memory block
	int rest = x%G_MEMORY_UNIT;

	// Memory block position
	int xpos = (x - rest) / G_MEMORY_UNIT;

	// Memory block pointer
	unsigned char * gval = (unsigned char *)((surface->pixels)+xpos+y*(surface->striplen));


	// Bit comparison
	unsigned char sum = 1U << ((G_MEMORY_UNIT-1) - rest);
	sum = sum & (*gval);

	if(sum == 0U){
		return 0U;
	}

	return 1U;
}


void g_draw_surface(G_Surface * canvas, G_Surface * draw, vec2 pos){

	// TODO implement direct memory reallocation. For now crappy for loops

	for(int y = 0; y < draw->height; y++){
		for(int x = 0; x < draw->width; x++){
			int p = g_get_pixel(draw, x, y);
			g_set_pixel(canvas, x+pos.x, y+pos.y, p);
		}
	}

}

void g_draw_alpha_over(G_Surface * canvas, G_Surface * draw, vec2 pos, char mask){
	
	for(int y = 0; y < draw->height; y++){
		for(int x = 0; x < draw->width; x++){
			int p = g_get_pixel(draw, x, y);
			mask = mask > 0 ? 1U : 0U;
			if(mask == p){
				g_set_pixel(canvas, x+pos.x, y+pos.y, p);	
			}
		}
	}

}

void g_invert_surface(G_Surface * surface, Rect rect){
	
	int xs = G_MEMORY_UNIT - (rect.x%G_MEMORY_UNIT);
	int xf = (rect.x+rect.width)%G_MEMORY_UNIT;
	for(int y = rect.y; (y < rect.y+rect.height && y < (int)surface->height); y++){
		for(int x = rect.x; x < rect.x+xs; x++){
			if(x < rect.x+rect.width){ 
				g_set_pixel(surface, x, y, !g_get_pixel(surface, x, y));
			}
		}
		int txs = rect.x+xs;
		while(txs+G_MEMORY_UNIT <= rect.x+rect.width && txs+G_MEMORY_UNIT <= surface->width){
			if(txs >= 0 && y >= 0) surface->pixels[txs/G_MEMORY_UNIT+y*surface->striplen] = 
				~surface->pixels[txs/G_MEMORY_UNIT+y*surface->striplen];
			txs = txs+G_MEMORY_UNIT;
		}
		for(int x = txs; x < txs+xf; x++){
			if(x < rect.x+rect.width) g_set_pixel(surface, x, y,
					!g_get_pixel(surface, x, y));
		}
	}

}

void g_clear(G_Surface * surface){

	memset(surface->pixels, 0, (G_MEMORY_UNIT/8)*surface->striplen*surface->height);

}
