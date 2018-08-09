#ifndef CCALCLC_SRC_GRAPHICS_UI_H_
#define CCALCLC_SRC_GRAPHICS_UI_H_

#include "common.h"
#include "math/rect.h"
#include "graphics/pixelsurface.h"

typedef struct{
	int sx;
	int sy;
	G_Surface * font;
	char * text;
	Rect rect;
	char autoscroll;
} G_ScrollText;

G_ScrollText * create_ScrollText(G_Surface * font, char autoscroll, Rect rect);

#endif
