#include "graphics/pixelbuffer.h"

const int G_MEMORY_UNIT = sizeof(unsigned int)*8;


G_PixelBuffer * g_create_buffer(unsigned int width, unsigned int height){

	G_PixelBuffer * buffer;

	// Divide the pixel array in int groups. One pixel = one bit, so there are sizeof(int) pixels in each group.
	int nrow = (width+(G_MEMORY_UNIT - (width % G_MEMORY_UNIT)))/G_MEMORY_UNIT;

	// Buffer allocation
	buffer = malloc(sizeof(G_PixelBuffer));
	buffer->width = width;
	buffer->striplen = nrow;
	buffer->height = height;
	buffer->pixels = (unsigned int *) calloc(nrow*height, (G_MEMORY_UNIT/8));

	return buffer;
}

void g_destroy_buffer(G_PixelBuffer * buffer){

	free(buffer->pixels);
	free(buffer);

}

void g_set_pixel(G_PixelBuffer * buffer, int x, int y, int val){

	// Box limitation to prevent overflow.
	if(((x < 0) | (x > buffer->width)) | ((y < 0) | (y > buffer->height))) return;

	//Relative x position in the memory block
	int rest = x%G_MEMORY_UNIT;

	// Memory block position
	int xpos = (x - rest) / G_MEMORY_UNIT;

	// Memory block pointer
	unsigned int * gval = (unsigned int *)((buffer->pixels)+xpos+y*(buffer->striplen));
	
	if(val == 0){
		
		// Bit substraction
		unsigned int sum = ~(1U << ((G_MEMORY_UNIT-1) - rest));
		sum = (*gval) & sum;
		*gval = sum;

	}else{
	
		// Bit addition
		unsigned int sum = 1U << ((G_MEMORY_UNIT-1) - rest);
		sum = (*gval) | sum;
		*gval = sum;

	}
}

int g_get_pixel(G_PixelBuffer * buffer, int x, int y){

	// Box limitation to prevent overflow.
	if(((x < 0) | (x > buffer->width)) | ((y < 0) | (y > buffer->height))) return 0;

	//Relative x position in the memory block
	int rest = x%G_MEMORY_UNIT;

	// Memory block position
	int xpos = (x - rest) / G_MEMORY_UNIT;

	// Memory block pointer
	unsigned int * gval = (unsigned int *)((buffer->pixels)+xpos+y*(buffer->striplen));


	// Bit comparison
	unsigned int sum = 1U << ((G_MEMORY_UNIT-1) - rest);
	sum = sum & (*gval);

	if(sum == 0){
		return 0;
	}

	return 1;
}


void g_clear(G_PixelBuffer * buffer){

	memset(buffer->pixels, 0, (G_MEMORY_UNIT/8)*buffer->striplen*buffer->height);

}
