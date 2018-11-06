#ifndef CCALCLC_SRC_GRAPHICS_UI_H_
#define CCALCLC_SRC_GRAPHICS_UI_H_

#include "common.h"
#include "math/rect.h"
#include "graphics/pixelsurface.h"
#include "graphics/font.h"
#include "graphics/renderer.h"
#include "graphics/scene.h"
#include "input.h"

typedef struct{
	int sx;
	int sy;
	G_Surface * font;
	char * text;
	Rect rect;
	char autoscroll;
} G_ScrollText;

G_ScrollText * g_create_scrolltext(G_Surface * font, char autoscroll, Rect rect);
void g_draw_scrolltext(G_Surface * buffer, G_ScrollText * scrolltext);
void g_destroy_scrolltext(G_ScrollText * scrolltext);

typedef struct{

	char is_pressed;
	G_Surface * up;
	G_Surface * down;
	Rect rect;

} G_ImageButton;

G_ImageButton * g_create_imagebutton(G_Surface * up, G_Surface * down, vec2 pos);
void g_draw_imagebutton(G_Surface * buffer, G_ImageButton * imagebutton);
void g_destroy_imagebutton(G_ImageButton * imagebutton);

typedef struct{

	char is_pressed;
	G_Surface * font;
	char * text;
	Rect rect;

} G_TextButton;

G_TextButton * g_create_textbutton(G_Surface * font, Rect rect);
void g_draw_textbutton(G_Surface * buffer, G_TextButton * textbutton);
void g_destroy_textbutton(G_TextButton * textbutton);

typedef struct{

	G_ScrollText ** list;
	char ** text;
	int size;
	int sizes;
	char sy;
	Rect rect;

} G_ScrollList;

G_ScrollList * g_create_scrolllist(int size, G_Surface * font, Rect rect);
void g_draw_scrolllist(G_Surface * surface, G_ScrollList * scrolllist);
void g_destroy_scrolllist(G_ScrollList * scrolllist);

void g_proccess_text_input(G_Scene * scene, G_ScrollText * scrolltext, int * cursor, int * startpoint);



#endif
