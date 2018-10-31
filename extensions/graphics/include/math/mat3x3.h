#ifndef CCALCLC_SRC_MATH_MAT3X3_H_
#define CCALCLC_SRC_MATH_MAT3X3_H_

#include "common.h"

#include "math/vec3.h"
#include <math.h>

/*
| M00, M03, M06 |
| M01, M04, M07 |
| M02, M05, M08 |
*/

typedef struct{
	float M0; float M3; float M6;
	float M1; float M4; float M7;
	float M2; float M5; float M8;
} mat3x3f;

mat3x3f mat3x3f_create();
mat3x3f mat3x3f_scale(mat3x3f mat, vec3 scalar);
vec3 mat3x3f_mul_vec3(mat3x3f mat, vec3 vec);
mat3x3f mat3x3f_mul_mat3x3f(mat3x3f mat, mat3x3f mat2);
mat3x3f mat3x3f_rot(mat3x3f mat, int x, int y, int z);
#endif
