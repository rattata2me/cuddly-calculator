#include "graphics/renderer.h"


// Bresenham's line algorithm TODO implement other line algorithm

void g_draw_line(G_PixelBuffer * buffer, vec2 origin, vec2 end, int color){

	vec2 dvec = vec2_minus(end, origin);

	int sx = sign(dvec.x);
	int sy = sign(dvec.y);
	dvec = vec2_abs(dvec);
	int acc = (dvec.x>dvec.y ? dvec.x : -dvec.y)/2;
	int cacc = 0;
	while(1){
		g_set_pixel(buffer, origin.x, origin.y, color);
		if(vec2_equal(origin, end)) break;
		cacc = acc;
		if(cacc > -(dvec.x)) {
			acc -= dvec.y;
			origin.x = origin.x + sx;
		}
		if(cacc < (dvec.y)) {
			acc += dvec.x;
			origin.y = origin.y + sy;
		}
	} 
}

// Crappy function TODO Fix this maybe?

void g_draw_rect(G_PixelBuffer * buffer, vec2 origin, vec2 size, int color){

	vec2 xvec = origin;
	xvec.x = xvec.x + size.x;
	vec2 yvec = origin;
	yvec.y = yvec.y + size.y;
	vec2 sumvec = vec2_sum(origin, size);

	g_draw_line(buffer, origin, yvec, color);
	g_draw_line(buffer, origin, xvec, color);
	g_draw_line(buffer, xvec, sumvec, color);
	g_draw_line(buffer, yvec, sumvec, color);

}

void g_fill_rect(G_PixelBuffer * buffer, vec2 origin, vec2 size, int color){

	for(int x = 0; x < size.x; x++){
		for(int y = 0; y < size.y; y++){
			vec2 t = vec2_add(origin, x, y);
			g_set_pixel(buffer, t.x, t.y, color);
		}
	}

}


// TODO: Clean this up, and optimize it

void internal_fill_line(G_PixelBuffer * buffer, vec2 point){

	int x = point.x;

	

	// Set the x into an edge
	while((g_get_pixel(buffer, (x-1), point.y) == 0) && (x > 0)){
		x--;
	}
	bool nwu = true;
	bool nwd = true;
	int s = x;
	while((g_get_pixel(buffer, x, point.y) == 0) && (x < buffer->width)){
		g_set_pixel(buffer, x, point.y, 1);
		x++;
	}
	int f = x;
	x = s;
	while(x < f){
		if((point.y+1) < buffer->height){
			int up = g_get_pixel(buffer, x, point.y+1);
			if(up == 0 && nwu){
				nwu = false;
				internal_fill_line(buffer, vec2_create(x, point.y+1));
			}else if(up == 1){
				nwu = true;
			}
		}
		if((point.y-1) >= 0){
			int up = g_get_pixel(buffer, x, point.y-1);
			if(up == 0 && nwd){
				nwd = false;
				internal_fill_line(buffer, vec2_create(x, point.y-1));
			}else if(up == 1){
				nwd = true;
			}
		}
		x++;
	}

}

void g_fill_shape(G_PixelBuffer * buffer, vec2 point){

	// Check that the given pixel is blank
	if(g_get_pixel(buffer, point.x, point.y) == 1) return;

	internal_fill_line(buffer, point);

} 