#include "programs/calc.h"
#include "graphics/scene.h"
#include "bigfont.h"
#include "smallfont.h"
#include "graphics/ui.h"
#include "mathinterpreter.h"

G_Surface * s, * b;

G_ScrollText * mathinput, * result;

int cursor = 0;
int startpoint = 0;

void calc_init(void * v_scene){

	G_Scene * scene = (G_Scene*)v_scene;
	scene->input_buffer = input_create_buffer();

	cursor = 0;
	startpoint = 0;

	//Font memory allocation
	b = g_create_surface_from_pixels(bigfont_width, bigfont_height, bigfont_pixels);
	s = g_create_surface_from_pixels(smallfont_width, smallfont_height, smallfont_pixels);

	mathinput = g_create_scrolltext(b, 2, rect_create(2,2,126,20));
	result = g_create_scrolltext(b, 2, rect_create(2, 40, 126, 20));

}


void update_mathinput(G_Scene * scene){
	
	char * ptext = mathinput->text;
	int mi_prev_len = str_len(ptext);

	mathinput->text = input_text(scene->input_buffer, mathinput->text, cursor);
	
	
	int mathinputlen = str_len(mathinput->text);

	if(mi_prev_len != mathinputlen){
		scene->need_update = 1;
		cursor += mathinputlen - mi_prev_len; 
	}

	if(input_get_key(scene->input_buffer, I_LEFT)){ 
		cursor --;
		input_set_key(scene->input_buffer, I_LEFT, 0);
	}
	if(input_get_key(scene->input_buffer, I_RIGHT)){
		cursor ++;
		input_set_key(scene->input_buffer, I_RIGHT, 0);
	}

	cursor = cursor > mathinputlen ? 0 : cursor;
	cursor = cursor < 0 ? mathinputlen : cursor;


	if(cursor > (mathinput->rect.width/g_font_size(mathinput->font).x)+startpoint-1)
		startpoint++;
	if(cursor <= startpoint) 
		startpoint -= 1;
	startpoint < 0 ? startpoint = 0 : 0;

	if(input_get_key(scene->input_buffer, I_RETURN)){
		free(mathinput->text);
		mathinput->text = str_new("");
		input_set_key(scene->input_buffer, I_RETURN, 0);
		scene->need_update = 1;
	}
	if(input_get_key(scene->input_buffer, I_ENTER)){
		// Process everything with mathinterpreter
		Mi_Err_Node error = mathinterpreter_error(MI_ERROR_NONE, "")->err;
		float res = mathinterpreter_eval(mathinput->text,  mathinputlen, &error);
		gcvt(res, 6, result->text);
		if(error.code == MI_ERROR_NONE) result->text = str_concat(str_new(" =  "), result->text);
		else result->text = str_new("Error");
		input_set_key(scene->input_buffer, I_ENTER, 0);
		scene->need_update = 1;
	}

	mathinput->sx = -g_font_size(mathinput->font).x*startpoint;
	// Draw everything
	g_clear(scene->buffer);
	g_draw_scrolltext(scene->buffer, mathinput);
	g_draw_line(scene->buffer, vec2_add(rect_pos(mathinput->rect), (cursor-startpoint)*g_font_size(mathinput->font).x, 0), 
			vec2_add(rect_pos(mathinput->rect), (cursor-startpoint)*g_font_size(mathinput->font).x, g_font_size(mathinput->font).y), 1);
	g_draw_scrolltext(scene->buffer, result);
	scene->need_update = 1;

}


void calc_draw(void * v_scene){
	
	G_Scene * scene = (G_Scene*)v_scene;
	
	update_mathinput(scene);
	
	/*Mi_Err_Node error = mathinterpreter_error(MI_ERROR_NONE, "")->err;
	float res = mathinterpreter_eval(cuddly->text, str_len(cuddly->text), &error);
	gcvt(res, 6, scrolltext->text);
	scrolltext->text = str_concat(str_new("Response = "), scrolltext->text);
	input_set_key(scene->input_buffer, I_ENTER, 0);*/

}


void calc_clear(void * v_scene){

	G_Scene * scene = (G_Scene*)v_scene;
	g_destroy_surface(scene->input_buffer);
	g_destroy_surface(s);
	g_destroy_surface(b);

}
