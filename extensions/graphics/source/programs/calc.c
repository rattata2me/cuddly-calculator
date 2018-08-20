#include "programs/calc.h"
#include "graphics/scene.h"
#include "bigfont.h"
#include "smallfont.h"
#include "graphics/ui.h"
#include "mathinterpreter.h"


G_Surface * s, * b;

G_ScrollText * mathinput, * result;

G_ScrollList * predictor_list;

int cursor = 0;
int ycursor = 0;
int startpoint = 0;
int functionlen = 0;

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
	predictor_list = g_create_scrolllist(6, s, rect_create(0,22,120,40));

}

void update_functionpredictor(G_Scene * scene){

	int start = cursor-functionlen;
	start = start < 0 ? 0 : start;

	mathinterpreterer_prepare_prediction(mathinput->text, start, cursor-1);
	int j = 0;
	for(int i = 0; i < MI_FUN_SIZE; i++){
		//printf("%i index %i start\n",functions_search_bool[i], start);
		if(!functions_search_bool[i] && j < predictor_list->size){
			free(predictor_list->text[j]);
			predictor_list->text[j] = str_new(functions[i]);
			j++;
		}
	}

	g_draw_scrolllist(scene->buffer, predictor_list);
	for(int i = 0; i < predictor_list->size; i++){
		if(ycursor == i) g_invert_surface(scene->buffer, predictor_list->list[i]->rect);
		free(predictor_list->text[i]);
		predictor_list->text[i] = str_new("");
	}

	if(input_get_key(scene->input_buffer, I_UP)){
		ycursor --;
		input_set_key(scene->input_buffer, I_UP, 0);
		scene->need_update = 1;
	}

	if(input_get_key(scene->input_buffer, I_DOWN)){
		ycursor ++;
		input_set_key(scene->input_buffer, I_DOWN, 0);
		scene->need_update = 1;
	}
	ycursor = ycursor < 0 ? predictor_list->rect.height/g_font_size(predictor_list->list[0]->font).y-1 : ycursor;
	ycursor = ycursor >= predictor_list->rect.height/g_font_size(predictor_list->list[0]->font).y ? 0 : ycursor;

}

void update_mathinput(G_Scene * scene){

	char * ptext = mathinput->text;
	int mi_prev_len = str_len(ptext);

	mathinput->text = input_text(scene->input_buffer, mathinput->text, cursor);


	int mathinputlen = str_len(mathinput->text);


	// SET CURSOR POSITION

	if(mi_prev_len != mathinputlen){
		scene->need_update = 1;

		cursor += mathinputlen - mi_prev_len;

	}

	if(input_get_key(scene->input_buffer, I_LEFT)){
		cursor --;
		input_set_key(scene->input_buffer, I_LEFT, 0);
		scene->need_update = 1;
	}

	if(input_get_key(scene->input_buffer, I_RIGHT)){
		cursor ++;
		input_set_key(scene->input_buffer, I_RIGHT, 0);
		scene->need_update = 1;
	}

	cursor = cursor > mathinputlen ? 0 : cursor;
	cursor = cursor < 0 ? mathinputlen : cursor;


	if(cursor > (mathinput->rect.width/g_font_size(mathinput->font).x)+startpoint-1)
		startpoint++;
	if(cursor <= startpoint)
		startpoint -= 1;
	startpoint < 0 ? startpoint = 0 : 0;


	// SPECIAL KEYS INPUT

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


	// FUNCTION "PREDICTION"
	int nlen = str_len(mathinput->text);
	if(mi_prev_len != nlen){
		if((mathinput->text[cursor-1]&0x5f) >= 67 && (mathinput->text[cursor-1]&0x5f) <= 90){
			functionlen += nlen - mi_prev_len;
			ycursor = 0;
		}else functionlen = 0;
	}


	mathinput->sx = -g_font_size(mathinput->font).x*startpoint;
	// Draw everything
	g_clear(scene->buffer);
	g_draw_scrolltext(scene->buffer, mathinput);
	g_draw_line(scene->buffer, vec2_add(rect_pos(mathinput->rect), (cursor-startpoint)*g_font_size(mathinput->font).x, 0),
			vec2_add(rect_pos(mathinput->rect), (cursor-startpoint)*g_font_size(mathinput->font).x, g_font_size(mathinput->font).y), 1);
	g_draw_scrolltext(scene->buffer, result);
	if(functionlen > 0){
		update_functionpredictor(scene);
	}
	scene->need_update = 1;

}


void calc_draw(void * v_scene){

	G_Scene * scene = (G_Scene*)v_scene;

	update_mathinput(scene);


}


void calc_clear(void * v_scene){

	G_Scene * scene = (G_Scene*)v_scene;
	g_destroy_surface(scene->input_buffer);
	g_destroy_surface(s);
	g_destroy_surface(b);

}
