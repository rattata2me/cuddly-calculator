#include "graphics/renderer.h"



// Bresenham's line algorithm TODO implement other line algorithm

void g_draw_line(G_Surface * surface, vec2 origin, vec2 end, int color){

	vec2 dvec = vec2_minus(end, origin);

	int sx = sign(dvec.x);
	int sy = sign(dvec.y);
	dvec = vec2_abs(dvec);
	int acc = (dvec.x>dvec.y ? dvec.x : -dvec.y)/2;
	int cacc = 0;
	while(1){
		g_set_pixel(surface, origin.x, origin.y, color);
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

void g_draw_rect(G_Surface * surface, Rect rect, int color){

	rect.height += -1;
	rect.width += -1;
	vec2 xvec = rect_pos(rect);
	xvec.x = xvec.x + rect.width;
	vec2 yvec = rect_pos(rect);
	yvec.y = yvec.y + rect.height;
	vec2 sumvec = vec2_sum(rect_pos(rect), rect_size(rect));

	g_draw_line(surface, rect_pos(rect), yvec, color);
	g_draw_line(surface, rect_pos(rect), xvec, color);
	g_draw_line(surface, xvec, sumvec, color);
	g_draw_line(surface, yvec, sumvec, color);

}

void g_fill_rect(G_Surface * surface, Rect rect, int color){

	int xs = G_MEMORY_UNIT - (rect.x%G_MEMORY_UNIT);
	int xf = (rect.x+rect.width)%G_MEMORY_UNIT;
	unsigned char col = color > 0 ? ~0 : 0;
	for(int y = rect.y; y < rect.y+rect.height && y < (int)surface->height; y++){
		for(int x = rect.x; x < rect.x+xs; x++){
			if(x < rect.x+rect.width){
				g_set_pixel(surface, x, y, color);
			}
		}
		int txs = rect.x+xs;
		while(txs+G_MEMORY_UNIT <= rect.x+rect.width && txs+G_MEMORY_UNIT <= surface->width){
			if(txs >= 0 && y >= 0) surface->pixels[(txs/G_MEMORY_UNIT)+y*surface->striplen] = col;
			txs = txs+G_MEMORY_UNIT;
		}
		for(int x = txs; x < txs+xf; x++){
			if(x < rect.x+rect.width) g_set_pixel(surface, x, y,
					color);
		}
	}

}


// TODO: Clean this up, and optimize it

void internal_fill_line(G_Surface * surface, vec2 point, unsigned int color){
	int x = point.x;

	// Negative color
	int ncolor = color > 0 ? 0U : 1U;

	// Set the x touching an edge.
	while((g_get_pixel(surface, (x-1), point.y) == ncolor) && (x > 0)){
		x--;
		g_set_pixel(surface, x, point.y, color);
	}
	// Set the starting pixel
	int b = x;

	x = point.x;

	// Draw the rest of the line
	while((g_get_pixel(surface, x, point.y) == ncolor) && (x < surface->width)){
		g_set_pixel(surface, x, point.y, color);
		x++;
	}

	// Set the final pixel location
	int f = x;
	x = b;

	// Check open path to call recursively the method
	int dir[] = {1, -1};
	bool nw[] = {true, true};
	unsigned int up;
	while(x < f){
		for(int i = 0; i < 2; i++){

			//	 TODO Also check in 8 directions.

			if(((point.y+dir[i]) < surface->height) && ((point.y+dir[i]) >= 0)){
				up = g_get_pixel(surface, x, (point.y+dir[i]));
				if(up == (ncolor) && nw[i]){
					nw[i] = false;
					internal_fill_line(surface, vec2_create(x, (point.y+dir[i])), color);
				}else if(up == color){
					nw[i] = true;
				}
			}
		}
		x++;
	}


}

void g_fill_shape(G_Surface * surface, vec2 point, unsigned int color){

	color = (color > 0U ? 1U : 0U);

	// Check that the given pixel is blank
	if(g_get_pixel(surface, point.x, point.y) == color) return;

	internal_fill_line(surface, point, color);

} 
