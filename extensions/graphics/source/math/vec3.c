#include "math/vec3.h"

vec3 vec3_create(int x, int y, int z){
	vec3 result = {x,y,z};
	return result;
}

vec3 vec3_add(vec3 point, int x, int y, int z){
	vec3 point2 = {point.x + x, point.y + y, point.z + z};
	return point2;
}

vec3 vec3_sum(vec3 point1, vec3 point2){
	vec3 result = {point1.x + point2.x, point1.y + point2.y, point1.z + point2.z};
	return result;
}

vec3 vec3_minus(vec3 point1, vec3 point2){
	vec3 result = {point1.x - point2.x, point1.y - point2.y, point1.z - point2.z};
	return result;
}

vec3 vec3_mul(vec3 point, int factor){
	return vec3_create(point.x*factor, point.y*factor, point.z*factor);
}

vec3 vec3_div(vec3 point, int factor){
	return vec3_create(point.x/factor, point.y/factor, point.z*factor);
}

vec3 vec3_abs(vec3 point){
	point.x = abs(point.x);
	point.y = abs(point.y);
	point.z = abs(point.z);
	return point;
}

bool vec3_equal(vec3 point1, vec3 point2){
	int result = (point1.x == point2.x) && (point1.y == point2.y) && (point1.z == point2.z);
	return result;
}
