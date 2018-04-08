#ifndef CCALCLC_SRC_GRAPHICS_TEXTURE_H_
#define CCALCLC_SRC_GRAPHICS_TEXTURE_H_

extern unsigned int BYTE_SIZE;

typedef struct{

	unsigned int width;
	unsigned int striplen;
	unsigned int height;
	unsigned char * pixels;

} G_Texture;

#endif