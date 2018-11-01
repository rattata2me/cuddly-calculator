#include "programs/graph.h"
#include "mathinterpreter.h"

#define precision 32
int values[precision];

vec2 oaxis;

void graph_init(void * v_scene){

	G_Scene * scene = (G_Scene*)v_scene;
	scene->input_buffer = input_create_buffer();

	scene->need_update = 1;



}

char * EXPRESSION = "X*X";

int px = 0;
float sx = 1;
int n;

void update_graph_values(G_Scene * scene){

	n = 128/precision;

	oaxis = vec2_create(scene->buffer->width/2, scene->buffer->height/2);

	int j = -64;
	for(int i = 0; i < precision; i++){
		MI_X = (float)(j+px)*sx;
		Mi_Err_Node error = mathinterpreter_error(MI_ERROR_NONE, "")->err;
		float res = mathinterpreter_eval(EXPRESSION,  str_len(EXPRESSION), &error);
		values[i] = (int)res;
		j+=n;
	}
}

void update_plane(G_Scene * scene){

	if(input_get_key(scene->input_buffer, I_LEFT)){
		px--;
		input_set_key(scene->input_buffer, I_LEFT, 0);
		scene->need_update = 1;
	}

	if(input_get_key(scene->input_buffer, I_RIGHT)){
		px++;
		input_set_key(scene->input_buffer, I_RIGHT, 0);
		scene->need_update = 1;
	}

	if(input_get_key(scene->input_buffer, I_UP)){
		sx *= 0.8f;
		input_set_key(scene->input_buffer, I_UP, 0);
		scene->need_update = 1;
	}

	if(input_get_key(scene->input_buffer, I_DOWN)){
		sx *= 1/0.8f;
		input_set_key(scene->input_buffer, I_DOWN, 0);
		scene->need_update = 1;
	}

	if(scene->need_update == 1){

		g_clear(scene->buffer);

		update_graph_values(scene);



		//Draw axis
		g_draw_line(scene->buffer, vec2_add(oaxis, -px, -32), vec2_add(oaxis, -px, 32), 1);
		g_draw_line(scene->buffer, vec2_add(oaxis, -64, 0), vec2_add(oaxis, 128, 0), 1);

		int j = 0;
		for(int x = 0; x < precision-1; x++){
			g_draw_line(scene->buffer, vec2_create(j, -values[x]+32), vec2_create(j+n, -values[x+1]+32), 1);
			j+=n;
		}



	}

}

void graph_draw(void * v_scene){

	G_Scene * scene = (G_Scene*)v_scene;
	update_plane(scene);

}

void graph_clear(void * v_scene){

}
