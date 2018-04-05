#ifndef CCALCLC_SRC_MATH_VEC2_H_
#define CCALCLC_SRC_MATH_VEC2_H_

#include "common.h"

typedef struct{
	int x;
	int y;
} vec2;

vec2 vec2_add(vec2 point, int x, int y);

vec2 vec2_sum(vec2 point1, vec2 point2);

vec2 vec2_minus(vec2 point1, vec2 point2);

vec2 vec2_abs(vec2 point);

vec2 vec2_create(int x, int y);

bool vec2_equal(vec2 point1, vec2 point2);

#endif