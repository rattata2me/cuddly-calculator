#include "math/vec2.h"

vec2 vec2_create(int x, int y){
	vec2 result = {x,y};
	return result;
}

vec2 vec2_add(vec2 point, int x, int y){
	point.x = point.x + x; point.y = point.y + y;
	return point;
}

vec2 vec2_sum(vec2 point1, vec2 point2){
	vec2 result = {(point1.x + point2.x), (point1.y + point2.y)};
	return result;
}

vec2 vec2_minus(vec2 point1, vec2 point2){
	vec2 result = {(point1.x - point2.x), (point1.y - point2.y)};
	return result;
}

vec2 vec2_abs(vec2 point){
	point.x = abs(point.x);
	point.y = abs(point.y);
	return point;
}

bool vec2_equal(vec2 point1, vec2 point2){
	int result = (point1.x == point2.x) && (point1.y == point2.y);
	return result;
}