#include "input.h"

G_Surface * input_create_buffer(){
	G_Surface * result = g_create_surface(16, 16);
	return result;
}

void input_set_key(G_Surface * input_buffer, unsigned char key, char val){
	g_set_pixel(input_buffer, key%G_MEMORY_UNIT, key/G_MEMORY_UNIT, val);
}

int input_get_key(G_Surface * input_buffer, unsigned char key){
	return g_get_pixel(input_buffer, key%G_MEMORY_UNIT, key/G_MEMORY_UNIT);
}
