#ifndef CCALCLC_SRC_GRAPHICS_PIXELBUFFER_H_
#define CCALCLC_SRC_GRAPHICS_PIXELBUFFER_H_

#include "common.h"

extern const int MEMORY_UNIT;


typedef struct{
	int width;
	int striplen;
	int height;
	unsigned int * pixels;

} G_PixelBuffer;


void g_create_buffer(G_PixelBuffer * buffer, unsigned int width, unsigned int height);

void g_destroy_buffer(G_PixelBuffer * buffer);

void g_set_pixel(G_PixelBuffer * buffer, int x, int y, char val);

char g_get_pixel(G_PixelBuffer * buffer, int x, int y);

#endif