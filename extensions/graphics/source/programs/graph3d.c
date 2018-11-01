#include "programs/graph3d.h"


mat3x3f transform;
vec3 translation;

float values[20];


void graph3d_init(void * v_scene){

	transform = mat3x3f_create();
	translation = vec3_create(0,0,0);

	for(int i = -10; i < 10, i++){
		values[i] = i*i;
	}

}


void draw_plane(G_Scene * v_scene){

	//Draw axis:
	vec3 lx = mat3x3f_mul_vec3(transform, vec3_create(1,0,0));


}

void graph3d_draw(void * v_scene){

	G_Scene * scene = (G_Scene*)v_scene;
	draw_plane(scene);

}

void graph3d_clear(void * v_scene){

}
