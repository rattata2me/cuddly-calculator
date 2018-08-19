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
	vec2 size = {scrolltext->font->width/FONT_SIZE, scrolltext->font->height/FONT_SIZE};
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

	scrolllist->size = size;
	scrolllist->rect = rect;
	int sizey = g_font_size(font).y;
	scrolllist->list = malloc(sizeof(G_ScrollText*)*(rect.height/sizey));
	scrolllist->text = malloc(sizeof(char*)*size);
	for(int i = 0; i < size; i++){
		scrolllist->text[i] = str_new("wdwwdd");
		if(i < rect.height/sizey) scrolllist->list[i] = g_create_scrolltext(font, 0, rect_create(rect.x, rect.y+sizey*i, rect.width, sizey));
	}
	return scrolllist;

}

void g_draw_scrolllist(G_Surface * surface, G_ScrollList * scrolllist){
	g_fill_rect(surface, scrolllist->rect, 0);
	g_draw_rect(surface, scrolllist->rect, 1);
	for(int i = 0; i < scrolllist->rect.height/g_font_size(scrolllist->list[0]->font).y; i++){
		free(scrolllist->list[i]->text);
		scrolllist->list[i]->text = str_new(scrolllist->text[i]);
		g_draw_scrolltext(surface, scrolllist->list[i]);
	}
}

void g_destroy_scrolllist(G_ScrollList * scrolllist){

	for(int i = 0; i < scrolllist->size; i++){
		free(scrolllist->text[i]);
		if(i < scrolllist->rect.height/g_font_size(scrolllist->list[0]->font).y) g_destroy_scrolltext(scrolllist->list[i]);
	}
	free(scrolllist->text);
	free(scrolllist->list);
	free(scrolllist);

}
