#include "math/rect.h"


Rect rect_create(int x, int y, int width, int height){
	Rect result = {x, y, width, height};
	return result;
}

vec2 rect_pos(Rect rect){
	return vec2_create(rect.x, rect.y);
}

vec2 rect_size(Rect rect){
	return vec2_create(rect.width, rect.height);
}

vec2 rect_middle(Rect rect){
	return vec2_create(rect.width/2+rect.x, rect.height/2+rect.y);
}
