#include "graphics/texture.h"

G_Surface * g_create_surface_from_pixels(unsigned int width, unsigned int height, unsigned char * pixels){

	G_Surface * surface;

	// Same system I used on the pixel buffer
	int ncol = (height+(G_MEMORY_UNIT - (height % G_MEMORY_UNIT)))/G_MEMORY_UNIT;

	// Texture Allocation
	surface = malloc(sizeof(G_Surface));
	surface->width = width;
	surface->striplen = ncol;
	surface->height = height;
	surface->is_static = 1;
	surface->pixels = pixels;

	return surface;

}
