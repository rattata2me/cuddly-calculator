#ifndef CCALCLC_SRC_MATH_VEC2_H_
#define CCALCLC_SRC_MATH_VEC2_H_

#include "common.h"

typedef struct{
	int x;
	int y;
	int z;
} vec3;

vec3 vec3_add(vec3 point, int x, int y, int z);

vec3 vec3_sum(vec3 point1, vec3 point2);

vec3 vec3_minus(vec3 point1, vec3 point2);

vec3 vec3_abs(vec3 point);

vec3 vec3_mul(vec3 point, int factor);

vec3 vec3_div(vec3 point, int factor);

vec3 vec3_create(int x, int y, int z);

bool vec3_equal(vec3 point1, vec3 point2);

#endif
