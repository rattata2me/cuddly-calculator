#include "programs/calc.h"

#include "optionsbutton.h"
#include "returnbutton.h"
#include "okbutton.h"

#include "mathinterpreter.h"

G_Surface * s, * b, * optsur, * oksur, * returnsur;

G_ScrollText * mathinput, * result, * enteroptions;

G_ScrollList * predictor_list, * options_list;

int cursor = 0;
int ycursor = 0;
int ycursors = 0; 
int startpoint = 0;
int functionlen = 0;

char scenesetc = 0;

void calc_init(void * v_scene){

	G_Scene * scene = (G_Scene*)v_scene;
	scene->input_buffer = input_create_buffer();

	cursor = 0;
	startpoint = 0;

	//Font memory allocation
	b = g_create_surface_from_pixels(bigfont_width, bigfont_height, bigfont_pixels);
	s = g_create_surface_from_pixels(smallfont_width, smallfont_height, smallfont_pixels);

	returnsur = g_create_surface_from_pixels(returnbutton_width, returnbutton_height, returnbutton_pixels);
	oksur = g_create_surface_from_pixels(okbutton_width, okbutton_height, okbutton_pixels);

	optsur = g_create_surface_from_pixels(optionsbutton_width, optionsbutton_height, optionsbutton_pixels);

	mathinput = g_create_scrolltext(b, 2, rect_create(2,2,126,20));
	result = g_create_scrolltext(b, 2, rect_create(2, 30, 126, 20));
	predictor_list = g_create_scrolllist(MI_FUN_SIZE, s, rect_create(0,22,120,36));

	//Options
	enteroptions = g_create_scrolltext(b, 2, rect_create(15, 50, 110, 14));
	options_list = g_create_scrolllist(6, s, rect_create(-1,-1,130,50));

}
char done = 0;
void update_functionpredictor(G_Scene * scene){

	if(functionlen > 0){

		if(!done)
			scene->need_update = 1;
		done = 1;
		int start = cursor-functionlen;
		start = start < 0 ? 0 : start;

		mathinterpreterer_prepare_prediction(mathinput->text, start, cursor-1);
		int j = 0;
		for(int i = 0; i < MI_FUN_SIZE; i++){
			if(!functions_search_bool[i] && j < predictor_list->size){
				free(predictor_list->text[j]);
				predictor_list->text[j] = str_new(functions[i]);
				j++;
			}
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
		if(scene->need_update){
			g_draw_scrolllist(scene->buffer, predictor_list);
			for(int i = 0; i < predictor_list->size; i++){
				if(i < predictor_list->sizes){
					if(ycursor == i) g_invert_surface(scene->buffer, predictor_list->list[i]->rect);
				}
				free(predictor_list->text[i]);
				predictor_list->text[i] = str_new("");
			}
		}

		if(ycursor < 0){
			predictor_list->sy --;
			ycursor = 0;
		}
		if(ycursor >= predictor_list->sizes){
			predictor_list->sy ++;
			ycursor = predictor_list->sizes-1;
		}
	}


}

void options_viewc(G_Scene * scene);

int timer = 0;

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
		functionlen = 0;
		input_set_key(scene->input_buffer, I_LEFT, 0);
		scene->need_update = 1;
	}

	if(input_get_key(scene->input_buffer, I_RIGHT)){
		cursor ++;
		functionlen = 0;
		input_set_key(scene->input_buffer, I_RIGHT, 0);
		scene->need_update = 1;
	}




	// FUNCTION "PREDICTION"
	int nlen = str_len(mathinput->text);
	if(mi_prev_len != nlen && cursor-1 >= 0){
		if((mathinput->text[cursor-1]&0x5f) >= 65 && (mathinput->text[cursor-1]&0x5f) <= 90){
			functionlen += nlen - mi_prev_len;
			functionlen = functionlen < 0 ? 0 : functionlen;
			ycursor = 0;
		}else functionlen = 0;
	}

	if(input_get_key(scene->input_buffer, I_ENTER)){
		// Process everything with mathinterpreter
		if(functionlen < 1){
			Mi_Err_Node error = mathinterpreter_error(MI_ERROR_NONE, "")->err;
			float res = mathinterpreter_eval(mathinput->text,  mathinputlen, &error);
			result->text = str_from_float(res);
			if(error.code == MI_ERROR_NONE)
				 result->text = str_concat(str_new("="), result->text);
			else result->text = str_new("Error");
		}else{
			char ** tmp = str_divide(mathinput->text, cursor);
			tmp[0] = str_shorten(tmp[0],functionlen);
			cursor -= functionlen;
			mathinput->text = str_concat(tmp[0], str_concat(str_new(predictor_list->list[ycursor]->text), tmp[1]));
			cursor += str_len(predictor_list->list[ycursor]->text);
			mathinputlen += str_len(predictor_list->list[ycursor]->text);
			functionlen = 0;
			done = 0;
		}
		input_set_key(scene->input_buffer, I_ENTER, 0);
		scene->need_update = 1;
	}

	cursor = cursor > mathinputlen ? 0 : cursor;
	cursor = cursor < 0 ? mathinputlen : cursor;


	if(cursor > (mathinput->rect.width/g_font_size(mathinput->font).x)+startpoint-1)
		startpoint++;
	if(cursor <= startpoint)
		startpoint -= 1;
	startpoint < 0 ? startpoint = 0 : 0;

	mathinput->sx = -g_font_size(mathinput->font).x*startpoint;

	if(timer % 50000 == 0) scene->need_update = 1;

	if(scene->need_update){
		// Draw everything
		g_clear(scene->buffer);
		g_draw_scrolltext(scene->buffer, mathinput);
		if((timer/50000 % 2) == 0)g_draw_line(scene->buffer, vec2_add(rect_pos(mathinput->rect), (cursor-startpoint)*g_font_size(mathinput->font).x, 0),
				vec2_add(rect_pos(mathinput->rect), (cursor-startpoint)*g_font_size(mathinput->font).x, g_font_size(mathinput->font).y), 1);
			g_draw_scrolltext(scene->buffer, result);
		g_draw_surface(scene->buffer, optsur, vec2_create(-2, scene->buffer->height-14));
	}

	update_functionpredictor(scene);

	timer++;

	if(input_get_key(scene->input_buffer, I_RETURN)){
		input_set_key(scene->input_buffer, I_RETURN, 0);
		scene->need_update = 1;
		scenesetc = 1;
		options_viewc(scene);
	}

}




int lopc = 0;
void setoptionsscrollistc(G_Scene * scene){
	lopc = options_list->rect.height/g_font_size(options_list->list[0]->font).y;
	for(int i = 0; i < options_list->size; i++){
		free(options_list->text[i]);
		switch(i){
			case 0:
				options_list->text[i] = str_new("Use radians[Y/N]");
				break;
			case 1:
				options_list->text[i] = str_new("Set x's value");
				break;
			case 2:
				options_list->text[i] = str_new("Set A's value");
				break;
			case 3:
				options_list->text[i] = str_new("Set B's value");
				break;
			case 4:
				options_list->text[i] = str_new("****");
				break;
			default:
				options_list->text[i] = str_new("*****");
				break;
		}
	}

}

int opyc = 0;
int opsc = 0;
unsigned char editingc = 0;
int cursorc = 0;
int startpointoc = 0;
void options_viewc(G_Scene * scene){

	if(editingc) g_proccess_text_input(scene, enteroptions, &cursorc, &startpointoc);

	int opscl = opsc;
	int opycl = opyc;

	if(!editingc){
		if(input_get_key(scene->input_buffer, I_UP)){
			opsc--;
			input_set_key(scene->input_buffer, I_UP, 0);
			scene->need_update = 1;
		}

		if(input_get_key(scene->input_buffer, I_DOWN)){
			opsc++;
			input_set_key(scene->input_buffer, I_DOWN, 0);
			scene->need_update = 1;
		}
	}

	opsc = opsc < 0 ? 0 : opsc;
	opsc  = opsc >= options_list->size ? options_list->size-1 : opsc;
	opyc = opsc > options_list->size-lopc ? options_list->size-lopc : opsc;

	if(opscl != opsc) options_list->list[opscl-opycl]->sx = 0;

	if(input_get_key(scene->input_buffer, I_ENTER)){
		if(editingc){
			int len = str_len(enteroptions->text);
			float val = 0.0f;
			switch (opsc) {
				case 0:;
					char * e = str_new("y");
					if(str_equal(enteroptions->text, e)){
						MI_USE_RADIANS = 1; 
					}else{
						MI_USE_RADIANS = 0;
					}
					free(e);
					break;
				case 1:
					val = mathinterpreter_get_value_from_str(enteroptions->text, 0, len-1);
					MI_X = val;
					break;
				default:
					break;
			}
			editingc = 0;
		}else{
			editingc = 1;
			free(enteroptions->text);
			enteroptions->text = str_new("");
			cursorc = 0;
			startpointoc = 0;
		}
		input_set_key(scene->input_buffer, I_ENTER, 0);
		scene->need_update = 1;
	}

	if((timer % 50000 == 0)){
		scene->need_update = 1;
		options_list->list[opsc-opyc]->sx -= 4;
	}
	timer++;

	if(scene->need_update){
		g_clear(scene->buffer);

		setoptionsscrollistc(scene);
		options_list->sy = opyc;
		g_draw_scrolllist(scene->buffer, options_list);
		g_invert_surface(scene->buffer, rect_create(0,g_font_size(options_list->list[0]->font).y*(opsc-opyc)-1, 128, g_font_size(options_list->list[0]->font).y));

		if(editingc){
			if((timer/50000 % 2) == 0){
				g_draw_line(scene->buffer, vec2_add(rect_pos(enteroptions->rect), (cursorc-startpointoc)*g_font_size(enteroptions->font).x, 0),
					vec2_add(rect_pos(enteroptions->rect), (cursorc-startpointoc)*g_font_size(enteroptions->font).x, g_font_size(enteroptions->font).y), 1);
			}
			g_draw_scrolltext(scene->buffer, enteroptions);
		}

		g_draw_surface(scene->buffer, returnsur, vec2_create(-2, scene->buffer->height-14));
		g_draw_surface(scene->buffer, oksur, vec2_create(-14+scene->buffer->width, scene->buffer->height-14));
	}
	if(input_get_key(scene->input_buffer, I_RETURN)){
		if(!editingc){
			scenesetc = 0;
			opyc = 0;
			opsc = 0;
			input_set_key(scene->input_buffer, I_RETURN, 0);
			scene->need_update = 1;
			update_mathinput(scene);
		}else{
			editingc = 0;
			input_set_key(scene->input_buffer, I_RETURN, 0);
		}

	}
}	



void calc_draw(void * v_scene){

	G_Scene * scene = (G_Scene*)v_scene;
	if(!scenesetc)update_mathinput(scene);
	else options_viewc(scene);

	if (input_get_key(scene->input_buffer, I_MENU)){

    	scene->programid = PROGRAM_MENU;
    	calc_clear(v_scene);
    	scene->need_update = 1;

    	input_set_key(scene->input_buffer, I_MENU, 0);
  	}

}


void calc_clear(void * v_scene){

	G_Scene * scene = (G_Scene*)v_scene;
	g_destroy_scrolltext(mathinput);
	g_destroy_scrolltext(result);
	g_destroy_scrolltext(enteroptions);
	g_destroy_scrolllist(predictor_list);
	g_destroy_scrolllist(options_list);
	g_destroy_surface(scene->input_buffer);
	g_destroy_surface(oksur);
	g_destroy_surface(returnsur);
	g_destroy_surface(optsur);
	g_destroy_surface(s);
	g_destroy_surface(b);

	opyc = 0;
	opsc = 0;
	editingc = 0;
	scenesetc = 0;
	cursorc = 0;
	startpointoc = 0;
	lopc = 0;
	cursor = 0;
	ycursor = 0;
	ycursors = 0;
	startpoint = 0;
	functionlen = 0;
	done = 0;

}
