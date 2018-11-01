#ifndef CCALCLC_SRC_PROGRAM_GRAPH3D_H_
#define CCALCLC_SRC_PROGRAM_GRAPH3D_H_

#include "math/mat3x3.h"
#include "math/vec3.h"

#include "graphics/scene.h"

#include "graphics/renderer.h"

void graph3d_init(void * v_scene);

void graph3d_draw(void * v_scene);

void graph3d_clear(void * v_scene);

#endif
