#include "math/rect.h"


Rect rect_create(int x, int y, int width, int height){
	Rect result = {x, y, width, height};
	return result;
}

