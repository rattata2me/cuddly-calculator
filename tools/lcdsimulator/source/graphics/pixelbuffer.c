#include "graphics/pixelbuffer.h"

const int G_MEMORY_UNIT = sizeof(int);


void g_create_buffer(G_PixelBuffer * buffer, unsigned int width, unsigned int height){


	// Divide the pixel array in int groups. One pixel = one bit, so there are sizeof(int) pixels in each group.
	int nrow = (width+(G_MEMORY_UNIT - (width % G_MEMORY_UNIT)))/G_MEMORY_UNIT;
	int ncol = height; // It is not necessary to reorder the height

	// Buffer allocation
	buffer = malloc(sizeof(G_PixelBuffer));
	buffer->width = width;
	buffer->striplen = nrow;
	buffer->height = height;
	buffer->pixels = (unsigned int *) malloc(nrow*G_MEMORY_UNIT*ncol);

}

void g_destroy_buffer(G_PixelBuffer * buffer){

	free(buffer->pixels);
	free(buffer);

}

void g_set_pixel(G_PixelBuffer * buffer, int x, int y, char val){

	int xpos = (x - (x%G_MEMORY_UNIT)) / G_MEMORY_UNIT;
	int gval = *((buffer->pixels)+xpos+y*(buffer->striplen));
	gval = 0;
	
}

char g_get_pixel(G_PixelBuffer * buffer, int x, int y){

	return 2;

}
