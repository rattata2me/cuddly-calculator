#ifndef CCALCLC_SRC_GRAPHICS_FONT_H_
#define CCALCLC_SRC_GRAPHICS_FONT_H_

#include "graphics/texture.h"

extern unsigned char FONT_SIZE;

void g_draw_text(G_Surface * canvas, G_Surface * bitmap,
		char * text, vec2 pos, vec2 size);

#endif

