#include "input.h"

G_Surface * input_create_buffer(){
	G_Surface * result = g_create_surface(16, 16);
	return result;
}

void input_set_key(G_Surface * input_buffer, unsigned char key, char val){
	g_set_pixel(input_buffer, key%(G_MEMORY_UNIT*input_buffer->striplen), 
			key/(G_MEMORY_UNIT*input_buffer->striplen), val);
}

int input_get_key(G_Surface * input_buffer, unsigned char key){
	return g_get_pixel(input_buffer, key%(G_MEMORY_UNIT*input_buffer->striplen), 
			key/(G_MEMORY_UNIT*input_buffer->striplen));
}


char * input_text(G_Surface * input_buffer, char * text){
	for(int i = 0; i < 256; i++){
		if(input_get_key(input_buffer, i) && i > 31 && i < 127){
			text = str_append(text, i);
			input_set_key(input_buffer, i, 0);
		}
		if(i == I_DEL && input_get_key(input_buffer, i)){
			text = str_shorten(text, 1);
			input_set_key(input_buffer, i, 0);			
		}
	}
	return text;
}
