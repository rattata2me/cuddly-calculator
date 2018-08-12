#ifndef CCALCLC_SRC_MATH_RECT_H_
#define CCALCLC_SRC_MATH_RECT_H_

#include "vec2.h"

typedef struct{
	int x;
	int y;
	int width;
	int height;
} Rect;

Rect rect_create(int x, int y, int width, int height);

vec2 rect_pos(Rect rect);

vec2 rect_size(Rect rect);

vec2 rect_middle(Rect rect);

#endif

