#include "programs/graph.h"
#include "mathinterpreter.h"


int values[128];

vec2 oaxis;

void graph_init(void * v_scene){

	G_Scene * scene = (G_Scene*)v_scene;
	scene->input_buffer = input_create_buffer();

	scene->need_update = 1;



}

char * EXPRESSION = "SIN(X*5)*32";

int px = -64;
float sx = 1;

void update_graph_values(G_Scene * scene){

	oaxis = vec2_create(scene->buffer->width/2, scene->buffer->height/2);

	for(int i = 0; i < 128; i++){
		MI_X = (float)(i+px)*sx;
		Mi_Err_Node error = mathinterpreter_error(MI_ERROR_NONE, "")->err;
		float res = mathinterpreter_eval(EXPRESSION,  str_len(EXPRESSION), &error);
		values[i] = (int)res;
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

		for(int x = 0; x < 128; x++){
			g_set_pixel(scene->buffer, x, -values[x]+32, 1);
		}



	}

}

void graph_draw(void * v_scene){

	G_Scene * scene = (G_Scene*)v_scene;
	update_plane(scene);

}

void graph_clear(void * v_scene){

}
