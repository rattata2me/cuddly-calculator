#ifndef CCALCLC_SRC_PROGRAM_GRAPH_H_
#define CCALCLC_SRC_PROGRAM_GRAPH_H_

#include "math/vec2.h"
#include "input.h"

#include "graphics/renderer.h"

#include "graphics/scene.h"


void graph_init(void * v_scene);

void update_graph_values(G_Scene * scene);

void graph_draw(void * v_scene);

void graph_clear(void * v_scene);

#endif
