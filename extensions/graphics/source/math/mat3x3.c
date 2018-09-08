#include "math/mat3x3.h"



mat3x3f mat3x3f_create(){
	mat3x3f result = {1.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,1.0f};
	return result;
}



/*
vec x, y, z
| M00*x, M03*y, M06*z |
| M01*x, M04*y, M07*z |
| M02*x, M05*y, M08*z |
*/
mat3x3f mat3x3f_scale(mat3x3f mat, vec3 scalar){
	mat3x3f result = mat;
	// first col          		// second col         		//third col
	result.M1 *= scalar.x;		result.M4 *= scalar.y;		result.M7 *= scalar.z;
	result.M2 *= scalar.x;		result.M5 *= scalar.y;		result.M8 *= scalar.z;
	result.M3 *= scalar.x;		result.M6 *= scalar.y;		result.M9 *= scalar.z;
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
	mat.M0*mat2.M0 + mat.M3*vec.y + mat.M6*vec.z,
	mat.M1*mat2.M0 + mat.M4*vec.y + mat.M7*vec.z,
	mat.M2*mat2.M0 + mat.M5*vec.y + mat.M8*vec.z

	};
}
