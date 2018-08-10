#ifndef CCALCLC_SRC_GRAPHICS_UI_H_
#define CCALCLC_SRC_GRAPHICS_UI_H_

#include "common.h"
#include "math/rect.h"
#include "graphics/pixelsurface.h"
#include "graphics/font.h"

typedef struct{
	int sx;
	int sy;
	G_Surface * font;
	char * text;
	Rect rect;
	char autoscroll;
} G_ScrollText;

G_ScrollText * create_scrolltext(G_Surface * font, char autoscroll, Rect rect);

void g_draw_scrolltext(G_Surface * buffer, G_ScrollText * scrolltext);

#endif
