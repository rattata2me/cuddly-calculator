#ifndef CCALCLC_SRC_GRAPHICS_SCENE_H_
#define CCALCLC_SRC_GRAPHICS_SCENE_H_

#include "graphics/pixelsurface.h"

typedef struct
{
	void (*init)(void * scene);
	void (*draw)(void * scene);
	void (*clear)(void * scene);

	char need_update;
	G_Surface * buffer;
	G_Surface * input_buffer;

} G_Scene;

#endif
