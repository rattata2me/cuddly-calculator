#ifndef CCALCLC_SRC_INPUT_H_
#define CCALCLC_SRC_INPUT_H_

#include "graphics/pixelsurface.h"

G_Surface * input_create_buffer();

void input_set_key(G_Surface * input_buffer, unsigned char key, char value);

int input_get_key(G_Surface * input_buffer, unsigned char key);

#endif
