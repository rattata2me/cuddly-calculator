#include "programs/graph.h"
#include "mathinterpreter.h"
#include "cursor.h"
#include "smallfont.h"
#include "bigfont.h"
#include "optionsbutton.h"
#include "scalebutton.h"
#include "movebutton.h"

#define precision 16
float values[precision];

vec2 oaxis;

G_Surface * s, * b, *cursors, *optsur, *scalesur, *movesur;
G_TextButton * infotab;
G_ScrollText * mathinput, * enterfun;

G_ScrollList * options_list;


void setoptionsscrollist(G_Scene * scene);

unsigned char sceneset = 0;
void graph_init(void * v_scene){

	G_Scene * scene = (G_Scene*)v_scene;
	scene->input_buffer = input_create_buffer();

	scene->need_update = 1;

	oaxis = vec2_create(scene->buffer->width/2, scene->buffer->height/2);

	b = g_create_surface_from_pixels(bigfont_width, bigfont_height, bigfont_pixels);
	s = g_create_surface_from_pixels(smallfont_width, smallfont_height, smallfont_pixels);
	optsur = g_create_surface_from_pixels(optionsbutton_width, optionsbutton_height, optionsbutton_pixels);
	scalesur = g_create_surface_from_pixels(scalebutton_width, scalebutton_height, scalebutton_pixels);
	movesur = g_create_surface_from_pixels(movebutton_width, movebutton_height, movebutton_pixels);


	cursors = g_create_surface_from_pixels(cursor_width, cursor_height, cursor_pixels);
	infotab = g_create_textbutton(s, rect_create(0,0,128,11));
	mathinput = g_create_scrolltext(b, 2, rect_create(2,20,126,20));
	enterfun = g_create_scrolltext(b, 0, rect_create(2,2,126,20));
	enterfun->text = str_new("Enter the function:");

	//Options
	options_list = g_create_scrolllist(6, s, rect_create(0,0,128,50));

}

int px = 1;
int py = 0;
float sx = 0.25f;
float sy = 0.25f;
int n;

void update_graph_values(G_Scene * scene){

	n = 128/precision;

	int j = -64;
	for(int i = 0; i < precision; i++){
		MI_X = (float)(j+px)*sx;
		Mi_Err_Node error = mathinterpreter_error(MI_ERROR_NONE, "")->err;
		float res = mathinterpreter_eval(mathinput->text,  str_len(mathinput->text), &error);
		values[i] = res;
		j+=n;
	}
}

unsigned char splane = 0;
void update_plane(G_Scene * scene){

	if(input_get_key(scene->input_buffer, I_ENTER)){
		splane = ~splane;
		input_set_key(scene->input_buffer, I_ENTER, 0);
		scene->need_update = 1;
	}

	if(splane){
		if(input_get_key(scene->input_buffer, I_UP)){
			sy *= 1/0.8f;
			input_set_key(scene->input_buffer, I_UP, 0);
			scene->need_update = 1;
		}
		if(input_get_key(scene->input_buffer, I_DOWN)){
			sy *= 0.8f;
			input_set_key(scene->input_buffer, I_DOWN, 0);
			scene->need_update = 1;
		}
		if(input_get_key(scene->input_buffer, I_LEFT)){
			sx *= 1/0.8f;
			input_set_key(scene->input_buffer, I_LEFT, 0);
			scene->need_update = 1;
		}

		if(input_get_key(scene->input_buffer, I_RIGHT)){
			sx *= 0.8f;
			input_set_key(scene->input_buffer, I_RIGHT, 0);
			scene->need_update = 1;
		}
	}else{
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
			py++;
			input_set_key(scene->input_buffer, I_UP, 0);
			scene->need_update = 1;
		}

		if(input_get_key(scene->input_buffer, I_DOWN)){
			py--;
			input_set_key(scene->input_buffer, I_DOWN, 0);
			scene->need_update = 1;
		}
	}

	if(scene->need_update == 1){

		g_clear(scene->buffer);

		update_graph_values(scene);

		//Draw cursor
		g_draw_surface(scene->buffer, cursors, vec2_add(oaxis, -4,-4));

		//Draw axis
		g_draw_line(scene->buffer, vec2_add(oaxis, -px, -32), vec2_add(oaxis, -px, 32), 1);
		g_draw_line(scene->buffer, vec2_add(oaxis, -64, py), vec2_add(oaxis, 128, py), 1);



		int j = 0;
		for(int x = 0; x < precision-1; x++){
			g_draw_line(scene->buffer, vec2_create(j, -values[x]*sy+32+py), vec2_create(j+n, -values[x+1]*sy+32+py), 1);
			j+=n;
		}

		//UI

		//info
		char * cx = str_from_float(px*sx);
		int lcx = str_len(cx);
		cx = str_shorten(cx, lcx -6);
		char * cy = str_from_float(py/sy);
		int lcy = str_len(cy);
		cy = str_shorten(cy, lcy -6);
		free(infotab->text);
		infotab->text = str_concat(str_concat(str_concat(str_new("X:"),cx), str_new(" Y:")),
		cy);
		g_draw_textbutton(scene->buffer, infotab);
		g_draw_surface(scene->buffer, optsur, vec2_create(-2, scene->buffer->height-14));

		if(splane) g_draw_surface(scene->buffer, scalesur, vec2_create(-14+scene->buffer->width, scene->buffer->height-14));
		else g_draw_surface(scene->buffer, movesur, vec2_create(-14+scene->buffer->width, scene->buffer->height-14));
	}
	if(input_get_key(scene->input_buffer, I_RETURN)){
		input_set_key(scene->input_buffer, I_RETURN, 0);
		scene->need_update = 1;
		sceneset = 2;
		options_view(scene);
	}

}


int cursor = 0;
int startpoint = 0;

unsigned int timer = 0;

void set_function(G_Scene * scene){


	g_proccess_text_input(scene, mathinput, &cursor, &startpoint);


	if(timer % 50000 == 0){
		scene->need_update = 1;
		enterfun->sx -= 8;
	}
	timer++;

	if(scene->need_update){

		g_clear(scene->buffer);

		if((timer/50000 % 2) == 0){
			g_draw_line(scene->buffer, vec2_add(rect_pos(mathinput->rect), (cursor-startpoint)*g_font_size(mathinput->font).x, 0),
				vec2_add(rect_pos(mathinput->rect), (cursor-startpoint)*g_font_size(mathinput->font).x, g_font_size(mathinput->font).y), 1);
		}

		g_draw_scrolltext(scene->buffer, mathinput);
		g_draw_scrolltext(scene->buffer, enterfun);
		g_draw_surface(scene->buffer, optsur, vec2_create(-2, scene->buffer->height-14));
	}

	if(input_get_key(scene->input_buffer, I_ENTER)){
		sceneset = 1;
		input_set_key(scene->input_buffer, I_ENTER, 0);
		scene->need_update = 1;
		update_plane(scene);
	}

}

void setoptionsscrollist(G_Scene * scene){

	for(int i = 0; i < 6; i++){
		free(options_list->text[i]);
		switch(i){
			case 0:
				options_list->text[i] = str_concat(str_new("X Pos:  "), str_from_float(px*sx));
				break;
			case 1:
				options_list->text[i] = str_concat(str_new("Y Pos:  "), str_from_float(py/sy));
				break;
			case 2:
				options_list->text[i] = str_concat(str_new("X Scale:  "), str_from_float(sx));
				break;
			case 3:
				options_list->text[i] = str_concat(str_new("Y Scale:  "), str_from_float(sy));
				break;
			default:
				options_list->text[i] = str_new(" ");
				break;
		}
	}

}

void options_view(G_Scene * scene){



}

void graph_draw(void * v_scene){

	G_Scene * scene = (G_Scene*)v_scene;
	if(sceneset == 1)update_plane(scene);
	else if(sceneset == 2) options_view(scene);
	else set_function(scene);
}

void graph_clear(void * v_scene){
	g_destroy_surface(s);
	g_destroy_surface(b);
	g_destroy_surface(cursors);
	g_destroy_surface(optsur);
	g_destroy_surface(movesur);
	g_destroy_surface(scalesur);
	g_destroy_textbutton(infotab);
	g_destroy_scrolltext(mathinput);
	g_destroy_scrolltext(enterfun);
}
