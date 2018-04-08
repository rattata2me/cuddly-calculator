

# Version 0.1
VERSION = 0.1

import PIL
from PIL import Image
import sys

BYTE_SIZE = 8



def convert_image(image_file, var_name):

	img = Image.open(image_file)
	img = img.convert("RGB")
	size = img.size
	sx = ((size[0] + (size[0] % BYTE_SIZE)) / BYTE_SIZE)
	sy = size[1]
	binary = []
	for y in range(sy):
		for x in range(sx):
			byte = 0
			for i in range(0, BYTE_SIZE):
				pixel = img.getpixel(((x+i), y))
				val = 1
				if pixel == (255, 255, 255):
					val = 0
				byte = ((byte<<1) | val)
			binary.append(hex(byte))
	var_name_file = var_name
	var_name = (var_name.split("/"))[-1]
	upper_str = "" \
	"// Auto-generated .C Image file " + str(VERSION) + "\n" \
	"unsigned char"
	upper_str = upper_str + " " + var_name + "_pixels[] = "
	binary_str = "{ \n\t"
	for i in range(len(binary)):
		if i == len(binary)-1:
			binary_str += binary[i]
		else:
			binary_str +=  binary[i] + ", "
		if ((i+1) % 10) == 0 and i != len(binary)-1:
			binary_str += "\n\t"
	final_str = (upper_str + binary_str + "\n};\n")
	final_str += "\n" + "unsigned int " + var_name + "_width = " + str(int(size[0])) + ";"
	final_str += "\n" + "unsigned int " + var_name + "_height = " + str(int(size[1])) + ";"
	output_file = open(var_name_file+".c", "w")
	output_file.write(final_str)
	output_file.close()

	header_str = "" \
	"// Auto-generated Header Image file " + str(VERSION) + "\n" \
	"#ifndef CCALCLC_SRC_IMAGES_" + var_name + "_H_\n" \
	"#define CCALCLC_SRC_IMAGES_" + var_name + "_H_\n" \
	"extern unsigned char " + var_name + "_pixels[" + str(int(sy*sx)) + "];\n" \
	"extern unsigned int " + var_name + "_width;\n" \
	"extern unsigned int " + var_name + "_height;\n" \
	"#endif\n"
	output_file = open(var_name_file+".h", "w")
	output_file.write(header_str)
	output_file.close()




sys.argv.pop(0)
if len(sys.argv) >= 2:
	var_name = (sys.argv[1])
	convert_image(sys.argv[0], var_name)

else:
	convert_image(sys.argv[0], (sys.argv[0].split("."))[0])