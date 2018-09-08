#include "math/mat3x3.h"



mat3x3f mat3x3f_create(){
	mat3x3f result = {1.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,1.0f};
	return result;
}

mat3x3f mat3x3f_scale(mat3x3f mat, vec3 scalar){
	mat3x3f result = mat;
	// first col          		// second col         		//third col
	result.M0 *= scalar.x;		result.M3 *= scalar.y;		result.M6 *= scalar.z;
	result.M1 *= scalar.x;		result.M4 *= scalar.y;		result.M7 *= scalar.z;
	result.M2 *= scalar.x;		result.M5 *= scalar.y;		result.M8 *= scalar.z;
	return result;
}

vec3 mat3x3f_mul_vec3(mat3x3f mat, vec3 vec){
	vec3 result = {
		mat.M0*vec.x + mat.M3*vec.y + mat.M6*vec.z,
		mat.M1*vec.x + mat.M4*vec.y + mat.M7*vec.z,
		mat.M2*vec.x + mat.M5*vec.y + mat.M8*vec.z
	};
	return result;
}

mat3x3f mat3x3f_mul_mat3x3f(mat3x3f mat, mat3x3f mat2){
	mat3x3f result = {
	//first col
	mat.M0*mat2.M0 + mat.M3*mat2.M1 + mat.M6*mat2.M2,
	mat.M1*mat2.M0 + mat.M4*mat2.M1 + mat.M7*mat2.M2,
	mat.M2*mat2.M0 + mat.M5*mat2.M1 + mat.M8*mat2.M2,

	//second col
	mat.M0*mat2.M3 + mat.M3*mat2.M4 + mat.M6*mat2.M5,
	mat.M1*mat2.M3 + mat.M4*mat2.M4 + mat.M7*mat2.M5,
	mat.M2*mat2.M3 + mat.M5*mat2.M4 + mat.M8*mat2.M5,

	//third col
	mat.M0*mat2.M6 + mat.M3*mat2.M7 + mat.M6*mat2.M8,
	mat.M1*mat2.M6 + mat.M4*mat2.M7 + mat.M7*mat2.M8,
	mat.M2*mat2.M6 + mat.M5*mat2.M7 + mat.M8*mat2.M8
	};
	return result;
}

mat3x3f mat3x3f_rot(mat3x3f mat, int x, int y, int z){
	mat3x3f result = mat;
	result = mat3x3f_mul_mat3x3f(result,
		cos(z), sin(z), 0,
		-sin(z), cos(z), 0,
		0, 0, 1
	);
	result = mat3x3f_mul_mat3x3f(result,
		cos(y), 0, -sin(y),
		0, 1, 0,
		sin(y), 0, cos(y)
	);
	result = mat3x3f_mul_mat3x3f(result,
		1, 0, 0,
		0, cos(x), sin(x),
		0, -sin(x), cos(x)
	);
	return result;
}

mat3x3f mat3x3f_add(mat3x3f mat, mat3x3f mat2){
	mat3x3f r = mat;
	r.M0 += mat2.M0; r.M3 += mat2.M3; r.M6 += mat2.M6;
	r.M1 += mat2.M1; r.M4 += mat2.M4; r.M7 += mat2.M7;
	r.M2 += mat2.M2; r.M5 += mat2.M5; r.M8 += mat2.M8;
	return r;
}
