#include "graphics/ui.h"

G_ScrollText * g_create_scrolltext(G_Surface * font, char autoscroll, Rect rect){
	G_ScrollText * scrolltext = malloc(sizeof(G_ScrollText));
	scrolltext->font = font;
	scrolltext->rect = rect;
	scrolltext->autoscroll = autoscroll;
	scrolltext->text = str_new("");
	scrolltext->sx = 0;
	scrolltext->sy = 0;
	return scrolltext;
}

void g_draw_scrolltext(G_Surface * buffer, G_ScrollText * scrolltext){
	if(scrolltext->autoscroll == 1){
		scrolltext->sx += -1;
	}
	vec2 size = g_font_size(scrolltext->font);
	int j = 0;
	int lline = 0;
	int line = 0;
	while(scrolltext->text[j] != '\0'){
		if((scrolltext->text[j] == '\n' || scrolltext->text[j+1] == '\0') &&
				scrolltext->sy+size.y*(line+1) <= scrolltext->rect.height &&
				scrolltext->sy+size.y*line >= 0){
			int len = j+(scrolltext->text[j] == '\n' ? 0 : 1) - lline;
			int s = (scrolltext->rect.width-len*size.x)/size.x;
			if(s < 2) s = 2;
			if(scrolltext->autoscroll) s = scrolltext->rect.width/size.x;
			int sx = ((len+s)*size.x + (scrolltext->sx%((len+s)*size.x)))
				% ((len+s)*size.x);

			int cx = sx;
			int c2x = sx - (len+s)*size.x;
			for(int i = 0; i < len; i++){

				// first text
				if(size.x + cx < scrolltext->rect.width){
					g_draw_word(buffer, scrolltext->font, scrolltext->text[lline+i], vec2_create(
							scrolltext->rect.x+cx, scrolltext->rect.y+size.y*line+scrolltext->sy) );
				}else if(c2x >= 0 && c2x+size.x < scrolltext->rect.width){
					g_draw_word(buffer, scrolltext->font, scrolltext->text[lline+i], vec2_create(
							scrolltext->rect.x+c2x, scrolltext->rect.y+size.y*line+scrolltext->sy) );
				}
				cx += size.x;
				c2x += size.x;
			}
			lline = j+1;
			line++;
		}
		j++;
	}

}

void g_destroy_scrolltext(G_ScrollText * scrolltext){
	free(scrolltext->text);
	free(scrolltext);
}


G_ImageButton * g_create_imagebutton(G_Surface * up, G_Surface * down, vec2 pos){

	G_ImageButton * imagebutton = malloc(sizeof(G_ImageButton));
	imagebutton->is_pressed = 0;
	imagebutton->up = up;
	imagebutton->down = down;
	imagebutton->rect = rect_create(pos.x, pos.y, up->width, up->height);
	return imagebutton;

}

void g_draw_imagebutton(G_Surface * buffer, G_ImageButton * imagebutton){

	if(imagebutton->is_pressed){
		g_draw_surface(buffer, imagebutton->down, vec2_create(imagebutton->rect.x, imagebutton->rect.y));
	}else{
		g_draw_surface(buffer, imagebutton->up, vec2_create(imagebutton->rect.x, imagebutton->rect.y));
	}

}

void g_destroy_imagebutton(G_ImageButton * imagebutton){
	free(imagebutton);
}

G_TextButton * g_create_textbutton(G_Surface * font, Rect rect){

	G_TextButton * textbutton = malloc(sizeof(G_TextButton));
	textbutton->font = font;
	textbutton->rect = rect;
	textbutton->is_pressed = 0;
	textbutton->text = str_new("");
	return textbutton;

}

void g_draw_textbutton(G_Surface * surface, G_TextButton * textbutton){
	int len = str_len(textbutton->text);
	vec2 size = g_font_size(textbutton->font);
	vec2 startpoint = vec2_minus(rect_middle(textbutton->rect),
			vec2_create(size.x*len/2, size.y/2));
	g_fill_rect(surface, textbutton->rect, 0);
	g_draw_text(surface, textbutton->font, textbutton->text, startpoint);
	g_draw_rect(surface, textbutton->rect, 1);
	if(textbutton->is_pressed) g_invert_surface(surface, textbutton->rect);
}

void g_destroy_textbutton(G_TextButton * textbutton){
	free(textbutton->text);
	free(textbutton);
}

G_ScrollList * g_create_scrolllist(int size, G_Surface * font, Rect rect){

	G_ScrollList * scrolllist = malloc(sizeof(G_ScrollList));
	scrolllist->sy = 0;
	scrolllist->size = size;
	scrolllist->rect = rect;
	int sizey = g_font_size(font).y;
	scrolllist->sizes = (rect.height/sizey);
	scrolllist->text = malloc(size * sizeof(char*));
	scrolllist->list = malloc(scrolllist->sizes * sizeof(G_ScrollText*));
	for(int i = 0; i < size; i++){
		scrolllist->text[i] = str_new("");
		if(i < scrolllist->sizes) scrolllist->list[i] = g_create_scrolltext(font, 0, rect_create(rect.x+1, rect.y+sizey*i, rect.width-1, sizey));
	}
	return scrolllist;

}

void g_draw_scrolllist(G_Surface * surface, G_ScrollList * scrolllist){
	g_fill_rect(surface, scrolllist->rect, 0);
	g_draw_rect(surface, scrolllist->rect, 1);
	scrolllist->sy = scrolllist->sy < 0 ? 0 : scrolllist->sy;
	scrolllist->sy = scrolllist->sy > scrolllist->size-scrolllist->sizes ? 
		scrolllist->size-scrolllist->sizes : scrolllist->sy;
	for(int i = 0; (i < scrolllist->sizes); i++){
		free(scrolllist->list[i]->text);
		scrolllist->list[i]->text = str_new(scrolllist->text[i+scrolllist->sy]);
		g_draw_scrolltext(surface, scrolllist->list[i]);
	}
}

void g_destroy_scrolllist(G_ScrollList * scrolllist){

	for(int i = 0; i < scrolllist->size; i++){
		free(scrolllist->text[i]);
		if(i < scrolllist->sizes) g_destroy_scrolltext(scrolllist->list[i]);
	}
	free(scrolllist->text);
	free(scrolllist->list);
	free(scrolllist);

}

void g_proccess_text_input(G_Scene * scene, G_ScrollText * scrolltext, int * cursor, int * startpoint){

	char * ptext = scrolltext->text;
	int prev_len = str_len(ptext);

	scrolltext->text = input_text(scene->input_buffer, scrolltext->text, *cursor);

	int scrolltextlen = str_len(scrolltext->text);

	if(prev_len != scrolltextlen){
		scene->need_update = 1;
		*cursor += scrolltextlen - prev_len;
	}

	if(input_get_key(scene->input_buffer, I_LEFT)){
		*cursor -=1;
		input_set_key(scene->input_buffer, I_LEFT, 0);
		scene->need_update = 1;
	}

	if(input_get_key(scene->input_buffer, I_RIGHT)){
		*cursor +=1;
		input_set_key(scene->input_buffer, I_RIGHT, 0);
		scene->need_update = 1;
	}

	*cursor = *cursor > scrolltextlen ? 0 : *cursor;
	*cursor = *cursor < 0 ? scrolltextlen : *cursor;

	if(*cursor > (scrolltext->rect.width/g_font_size(scrolltext->font).x)+(*startpoint)-1)
		(*startpoint) +=1;
	if(*cursor <= *startpoint)
		(*startpoint) -=1;
	(*startpoint) < 0 ? (*startpoint) = 0 : 0;

	scrolltext->sx = -g_font_size(scrolltext->font).x*(*startpoint);

}
