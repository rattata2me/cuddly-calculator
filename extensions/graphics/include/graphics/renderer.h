#ifndef CCALCLC_SRC_GRAPHICS_RENDERER_H_
#define CCALCLC_SRC_GRAPHICS_RENDERER_H_

#include "common.h"
#include "graphics/pixelsurface.h"
#include "math/vec2.h"

void g_draw_line(G_Surface * surface, vec2 origin, vec2 end, int color);

void g_draw_rect(G_Surface * surface, Rect rect, int color);

void g_fill_rect(G_Surface * surface, Rect rect, int color);

void g_fill_shape(G_Surface * surface, vec2 point, unsigned int color);

#endif
