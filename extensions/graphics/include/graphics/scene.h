#ifndef CCALCLC_SRC_GRAPHICS_SCENE_H_
#define CCALCLC_SRC_GRAPHICS_SCENE_H_

#include "graphics/pixelsurface.h"

typedef struct
{

	char programid;
	char need_update;
	G_Surface * buffer;
	G_Surface * input_buffer;

} G_Scene;

#define PROGRAM_MENU 0
#define PROGRAM_CALC 1
#define PROGRAM_GRAPH 2


#endif
