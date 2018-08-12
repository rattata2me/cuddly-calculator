#ifndef CCALCLC_SRC_GRAPHICS_PIXELBUFFER_H_
#define CCALCLC_SRC_GRAPHICS_PIXELBUFFER_H_

#include "common.h"
#include "math/vec2.h"
#include "math/rect.h"

extern int G_MEMORY_UNIT;


typedef struct{

	unsigned int width;
	int striplen;
	unsigned int height;
	unsigned char * pixels;

} G_Surface;


G_Surface * g_create_surface(unsigned int width, unsigned int height);

void g_destroy_surface(G_Surface * surface);

void g_set_pixel(G_Surface * surface, int x, int y, int val);

int g_get_pixel(G_Surface * surface, int x, int y);

void g_draw_surface(G_Surface * canvas, G_Surface * draw, vec2 pos);

void g_draw_alpha_over(G_Surface * canvas, G_Surface * draw, vec2 pos, char mask);

void g_invert_surface(G_Surface * surface, Rect rect);

void g_clear(G_Surface * surface);

#endif
