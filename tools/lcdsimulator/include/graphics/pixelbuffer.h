#ifndef CCALCLC_SRC_GRAPHICS_PIXELBUFFER_H_
#define CCALCLC_SRC_GRAPHICS_PIXELBUFFER_H_

#include "common.h"

extern const int MEMORY_UNIT;


typedef struct{

	unsigned int width;
	unsigned int striplen;
	unsigned int height;
	unsigned int * pixels;

} G_PixelBuffer;


G_PixelBuffer * g_create_buffer(unsigned int width, unsigned int height);

void g_destroy_buffer(G_PixelBuffer * buffer);

void g_set_pixel(G_PixelBuffer * buffer, int x, int y, int val);

int g_get_pixel(G_PixelBuffer * buffer, int x, int y);

void g_clear(G_PixelBuffer * buffer);

#endif