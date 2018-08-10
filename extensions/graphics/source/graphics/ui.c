#include "graphics/ui.h"

G_ScrollText * g_create_scrolltext(G_Surface * font, char autoscroll, Rect rect){
	G_ScrollText * scrolltext = malloc(sizeof(G_ScrollText));
	scrolltext->font = font;
	scrolltext->rect = rect;
	scrolltext->autoscroll = autoscroll;
	scrolltext->text = "\0";
	scrolltext->sx = 0;
	scrolltext->sy = 0;
	return scrolltext;
}

void g_draw_scrolltext(G_Surface * buffer, G_ScrollText * scrolltext){
	if(scrolltext->autoscroll){
		scrolltext->sx += -1;
	}
	vec2 size = {scrolltext->font->width/FONT_SIZE, scrolltext->font->height/FONT_SIZE};	
	int j = 0;
	int lline = 0;
	int line = 0;
	while(scrolltext->text[j] != '\0'){
		if((scrolltext->text[j] == '\n' || scrolltext->text[j+1] == '\0') && 
				scrolltext->sy+size.y*(line+1) < scrolltext->rect.height && 
				scrolltext->sy+size.y*line >= 0){
			int len = j+(scrolltext->text[j] == '\n' ? 0 : 1) - lline;
			int s = (scrolltext->rect.width-len*size.x)/size.x;
			if(s < 2) s = 2;
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
	g_destroy_surface(scrolltext->font);
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
