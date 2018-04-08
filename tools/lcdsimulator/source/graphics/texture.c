#include "graphics/texture.h"

unsigned int BYTE_SIZE = 8;

G_Texture * g_create_texture(unsigned int width, unsigned int height, char * pixels){

	G_Texture * texture;

	// Same system I used on the pixel buffer
	int nrow = (width+(BYTE_SIZE - (width % BYTE_SIZE)))/BYTE_SIZE;

	// Texture Allocation
	tetxure = malloc(sizeof(G_Texture));
	texture->width = width;
	texture->striplen = nrow;
	texture->height = height;
	texture->pixels = pixels;

	return texture;

}