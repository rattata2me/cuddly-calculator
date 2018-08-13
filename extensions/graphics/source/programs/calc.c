#include "programs/calc.h"
#include "graphics/scene.h"
#include "bigfont.h"
#include "smallfont.h"
#include "graphics/ui.h"
#include "logo.h"
#include "mathinterpreter.h"

G_Surface * texture, * s, * b;

G_ScrollText * scrolltext, * cuddly;

G_TextButton * textbutton;



void calc_init(void * v_scene){

	G_Scene * scene = (G_Scene*)v_scene;
	scene->input_buffer = input_create_buffer();
	texture = g_create_surface_from_pixels(logo_width, logo_height, logo_pixels);
	b = g_create_surface_from_pixels(bigfont_width, bigfont_height, bigfont_pixels);
	s = g_create_surface_from_pixels(smallfont_width, smallfont_height, smallfont_pixels);
	scrolltext = g_create_scrolltext(s, 0, rect_create(5, 25, 120, 40));
	cuddly = g_create_scrolltext(s, 0, rect_create(10, 1, 120, 20));
	cuddly->text = str_new("");
	textbutton = g_create_textbutton(s, rect_create(1, 35, 65, 13));
	textbutton->text = str_new("brand-new");
}



void calc_draw(void * v_scene){
	
	G_Scene * scene = (G_Scene*)v_scene;

	g_clear(scene->buffer);
	//g_draw_scrolltext(scene->buffer, scrolltext);
	g_draw_scrolltext(scene->buffer, cuddly);

	cuddly->text = input_text(scene->input_buffer, cuddly->text);

	if(input_get_key(scene->input_buffer, I_RETURN)){
		free(cuddly->text);
		cuddly->text = str_new("");
		input_set_key(scene->input_buffer, I_RETURN, 0);
	}
	if(input_get_key(scene->input_buffer, I_ENTER)){
		//calc
		Mi_Err_Node error = mathinterpreter_error(MI_ERROR_NONE, "")->err;
		float res = mathinterpreter_eval(cuddly->text, str_len(cuddly->text), &error);
		gcvt(res, 6, scrolltext->text);
		scrolltext->text = str_concat(str_new("Response = "), scrolltext->text);
		input_set_key(scene->input_buffer, I_ENTER, 0);
	}
	g_draw_scrolltext(scene->buffer, scrolltext);
	//g_draw_text(buffer, b, "1. Big Font", vec2_create(1,10));
	//g_draw_text(buffer, s, "2. Small Font", vec2_create(2, 40));
	//g_draw_scrolltext(buffer, scrolltext);
	//g_draw_scrolltext(buffer, cuddly);
	//g_invert_surface(buffer, rect_create((k%600)/7, (k%600)/7, 70, 40));
	//g_fill_rect(buffer, rect_create(0,0,128, 64), 1);
	//g_draw_textbutton(buffer, textbutton);
	//textbutton->rect.x = 128-(k%700)/7;
	//textbutton->rect.y = 64-(k%700)/7;
	//g_draw_surface(scene->buffer, scene->input_buffer, vec2_create(0,0));
	//g_draw_surface(buffer, c, vec2_create(16*2, 10));
	//g_draw_surface(buffer, texture, vec2_create(-1,-5));
	//g_draw_rect(buffer, vec2_create(k/10,1), vec2_create(10,10), 1);
	//g_draw_rect(buffer, vec2_create(100-k/5,20), vec2_create(10,10), 1);
	//g_fill_shape(buffer, vec2_create(12, 13), 1U);
	//g_fill_shape(buffer, vec2_create(12, 13), 0U);
	
}


void calc_clear(void * v_scene){

	//G_Scene * scene = (G_Scene*)v_scene;
}
