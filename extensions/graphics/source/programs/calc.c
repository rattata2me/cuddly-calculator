#include "programs/calc.h"
#include "graphics/scene.h"
#include "bigfont.h"
#include "smallfont.h"
#include "graphics/ui.h"
#include "mathinterpreter.h"

G_Surface * s, * b;

G_ScrollText * mathinput;



void calc_init(void * v_scene){

	G_Scene * scene = (G_Scene*)v_scene;
	scene->input_buffer = input_create_buffer();

	//Font memory allocation
	b = g_create_surface_from_pixels(bigfont_width, bigfont_height, bigfont_pixels);
	s = g_create_surface_from_pixels(smallfont_width, smallfont_height, smallfont_pixels);

	mathinput = g_create_scrolltext(b, 0, rect_create(2,2,126,20));

}

void update_mathinput(G_Scene * scene){
	
	char * ptext = mathinput->text;
	mathinput->text = input_text(scene->input_buffer, mathinput->text, str_len(mathinput->text));
	
	if(ptext != mathinput->text){
		if(input_get_key(scene->input_buffer, I_RETURN)){
			free(mathinput->text);
			mathinput->text = str_new("");
			input_set_key(scene->input_buffer, I_RETURN, 0);
		}
		if(input_get_key(scene->input_buffer, I_ENTER)){
			// Process everything with mathinterpreter
			input_set_key(scene->input_buffer, I_ENTER, 0);
		}
		// Draw everything
		g_clear(scene->buffer);		
		g_draw_scrolltext(scene->buffer, mathinput);
		scene->need_update = 1;
	}
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
