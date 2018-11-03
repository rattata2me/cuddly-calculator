#ifndef CCALCLC_SRC_INPUT_H_
#define CCALCLC_SRC_INPUT_H_

#include "graphics/pixelsurface.h"

// Key defininitions

#define I_ENTER 13
#define I_RETURN 9
#define I_DEL 127
#define I_MENU 27
#define I_UP 220
#define I_DOWN 221
#define I_RIGHT 222
#define I_LEFT 223



G_Surface * input_create_buffer();

void input_set_key(G_Surface * input_buffer, unsigned char key, char value);

unsigned char input_get_key(G_Surface * input_buffer, unsigned char key);

char * input_text(G_Surface * input_buffer, char * str, int cursor);


#endif
