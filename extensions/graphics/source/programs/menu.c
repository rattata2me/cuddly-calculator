#include "programs/menu.h"

#include "graphicon.h"
#include "bigfont.h"

typedef struct{
  G_Surface * surface;
  char * text;
  char programid;
}Program_entry;

#define n_entries 2

Program_entry entries[2];

G_Surface * b;

G_ScrollText * progvalue;

void menu_init(void * v_scene){

  G_Scene * scene = (G_Scene*)v_scene;
  scene->input_buffer = input_create_buffer();

  scene->need_update = 1;

  entries[0] = (Program_entry) {g_create_surface_from_pixels(graphicon_width, graphicon_height, graphicon_pixels), str_new("Calculator"), PROGRAM_CALC};
  entries[1] = (Program_entry) {g_create_surface_from_pixels(graphicon_width, graphicon_height, graphicon_pixels), str_new("Graph"), PROGRAM_GRAPH};

  b = g_create_surface_from_pixels(bigfont_width, bigfont_height, bigfont_pixels);

  progvalue = g_create_scrolltext(b, 2, rect_create(2, 50, 128, 14));
  free(progvalue->text);
  progvalue->text = entries[0].text;

}

int current = 0;

void menu_draw(void * v_scene){

  G_Scene * scene = (G_Scene*)v_scene;

  if(input_get_key(scene->input_buffer, I_LEFT)){
    current--;
    current = current < 0 ? 0 : current;
    progvalue->text = entries[current].text;
    input_set_key(scene->input_buffer, I_LEFT, 0);
    scene->need_update = 1;
  }

  if(input_get_key(scene->input_buffer, I_RIGHT)){
    current++;
    current = current >= n_entries ? n_entries-1 : current;
    progvalue->text = entries[current].text;
    input_set_key(scene->input_buffer, I_RIGHT, 0);
    scene->need_update = 1;
  }

  if(scene->need_update){

    g_clear(scene->buffer);

    for(int i = 0; i < n_entries; i++){
      g_draw_surface(scene->buffer, entries[i].surface, vec2_create(i*32, 0));
      if(i == current) g_invert_surface(scene->buffer, rect_create(i*32, 0, 32, 32));
    }
    g_draw_scrolltext(scene->buffer, progvalue);
  }

  if(input_get_key(scene->input_buffer, I_ENTER)){

    scene->programid = entries[current].programid;
    menu_clear(v_scene);
    scene->need_update = 1;

    input_set_key(scene->input_buffer, I_ENTER, 0);
  }

}

void menu_clear(void * v_scene){
  for(int i = 0; i < n_entries; i++){
    g_destroy_surface(entries[i].surface);
    if(i != current)free(entries[i].text);
  }
  current = 0;
  g_destroy_scrolltext(progvalue);
  g_destroy_surface(b);
}
