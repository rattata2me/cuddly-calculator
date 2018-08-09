#ifndef CCALCLC_SRC_MATH_RECT_H_
#define CCALCLC_SRC_MATH_RECT_H_

typedef struct{
	int x;
	int y;
	int width;
	int height;
} Rect;

Rect create_rect(int x, int y, int width, int height);

#endif

