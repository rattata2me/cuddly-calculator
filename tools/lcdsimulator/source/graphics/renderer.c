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