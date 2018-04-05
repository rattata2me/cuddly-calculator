#ifndef CCALCLC_SRC_GRAPHICS_RENDERER_H_
#define CCALCLC_SRC_GRAPHICS_RENDERER_H_

#include "common.h"
#include "graphics/pixelbuffer.h"
#include "math/vec2.h"

void g_draw_line(G_PixelBuffer * buffer, vec2 origin, vec2 end, int color);

#endif