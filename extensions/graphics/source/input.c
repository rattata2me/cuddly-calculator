#include "input.h"

G_Surface * input_create_buffer(){
	G_Surface * result = g_create_surface(16, 16);
	return result;
}

void input_set_key(G_Surface * input_buffer, unsigned char key, char val){
	g_set_pixel(input_buffer, key/(G_MEMORY_UNIT*input_buffer->striplen),
		key%(G_MEMORY_UNIT*input_buffer->striplen), val);
}

unsigned char input_get_key(G_Surface * input_buffer, unsigned char key){
	return g_get_pixel(input_buffer, key/(G_MEMORY_UNIT*input_buffer->striplen),
		key%(G_MEMORY_UNIT*input_buffer->striplen));
}


char * input_text(G_Surface * input_buffer, char * text, int cursor){
	for(int i = 31; i < 127; i++){
		if(input_get_key(input_buffer, i)){
			char ** tmp =  str_divide(text, cursor);

			tmp[0] = str_append(tmp[0], i);
			text = str_concat(tmp[0], tmp[1]);

			input_set_key(input_buffer, i, 0);
			return text;
		}
	}
	if(input_get_key(input_buffer, I_DEL)){
		char ** tmp = str_divide(text, cursor);

		tmp[0] = str_shorten(tmp[0], 1);
		text = str_concat(tmp[0], tmp[1]);

		input_set_key(input_buffer, I_DEL, 0);
		return text;
	}
	return text;
}
