#!/usr/bin/env python

# Version 0.1
VERSION = 0.1

import PIL
from PIL import Image, ImageFont, ImageDraw
import sys
import os

BYTE_SIZE = 8


def get_binary_str(binary):

	binary_str = "{ \n\t"
	for i in range(len(binary)):
		if i == len(binary)-1:
			binary_str += binary[i]
		else:
			binary_str +=  binary[i] + ", "
		if ((i+1) % 10) == 0 and i != len(binary)-1:
			binary_str += "\n\t"
	binary_str += "\n}"
	return binary_str

def convert_image(image_file, var_name):

	img = Image.open(image_file)
	img = img.convert("RGB")
	size = img.size
	sy = ((size[1] + (BYTE_SIZE - (size[1] % BYTE_SIZE))) / BYTE_SIZE)
	sx = size[0]
	binary = []
	print sy
	for x in range(sx):
		for y in range(sy):
			byte = 0
			for i in range(BYTE_SIZE):
				py = y*BYTE_SIZE+i
				if py >= size[1]:
					py = size[1]-1
				pixel = img.getpixel((x, py))
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
	binary_str = get_binary_str(binary)
	final_str = (upper_str + binary_str + ";\n")
	final_str += "\n" + "unsigned int " + var_name + "_width = " + str(int(size[0])) + ";"
	final_str += "\n" + "unsigned int " + var_name + "_height = " + str(int(size[1])) + ";"
	output_file = open(var_name_file+".c", "w")
	output_file.write(final_str+"\n")
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

def convert_font(image_folder, var_name):
	files = os.listdir(image_folder)
	image_files = []
	for i in files:
		if ".bmp" in i and i.split(".")[0]:
			image_files.append(i.split(".")[0])

	var_name_file = var_name
	var_name = (var_name.split("/"))[-1]

	upper_str = ""

	indices = []

	size = [0,0]
        sx = 0
	g = 0
	for image_file in image_files:
		indices.append(image_file[0])
		image_file = image_folder + "/" + image_file + ".bmp"
		img = Image.open(image_file)
		img = img.convert("RGB")
		size = img.size
                size[0] -= 1
		sx = ((size[0] + (BYTE_SIZE - (size[0] % BYTE_SIZE))) / BYTE_SIZE)
		sy = size[1]
		binary = []
		for y in range(sy):
			for x in range(sx):
				byte = 0
				for i in range(BYTE_SIZE):
					px = x*BYTE_SIZE+i
					if px >= size[0]:
						px = size[0]-1
					pixel = img.getpixel((px, y))
					val = 1
					if pixel == (255, 255, 255):
						val = 0
					byte = ((byte<<1) | val)
				binary.append(hex(byte))

		binary_str = "\n\t" + get_binary_str(binary).replace("\n", "\n\t")
		upper_str += binary_str + ","
		g += 1

	upper_str = upper_str[:-1]
        bin_str = upper_str
        upper_str = "" \
        "// Auto-generated .C Image file " + str(VERSION) + "\n" \
        "\nunsigned char"
        upper_str = upper_str + " " + var_name + "_pixels[][" + str(sx*size[1]) + "] = {\n"

        upper_str += bin_str

        upper_str += "\n};\n\nchar " + var_name + "_indices[] = {\n"

	c = 0
	for i in indices:
		if c == 0:
			upper_str += "\n\t"

		upper_str += str(hex(ord(i))) + ", "
		c += 1
		if c == 8:
			c = 0
	upper_str = upper_str[:-2]
	upper_str += "\n}"
	upper_str += "\n\n" + "unsigned int " + var_name + "_width = " + str(int(size[0])) + ";"
	upper_str += "\n" + "unsigned int " + var_name + "_height = " + str(int(size[1])) + ";"
        upper_str += "\n" + "unsigned int " + var_name + "_size = " + str(g) + ";"

	header_str = "" \
	"// Auto-generated Header Image file " + str(VERSION) + "\n" \
	"#ifndef CCALCLC_SRC_FONTS_" + var_name + "_H_\n" \
	"#define CCALCLC_SRC_FONTS_" + var_name + "_H_\n" \
	"extern unsigned char " + var_name + "_pixels["+str(g)+"][" + str(sx) + "];\n" \
	"extern unsigned int " + var_name + "_width;\n" \
	"extern unsigned int " + var_name + "_height;\n" \
        "extern unsigned int " + var_name + "_size;\n" \
	"#endif\n"
	output_file = open(var_name_file+".h", "w")
	output_file.write(header_str)
	output_file.close()

	output_file = open(var_name_file+".c", "w")
        output_file.write(upper_str + "\n")
	output_file.close()

chr_map = open('ASCII.txt', 'r').read()

def generatefont_internal(font_name, size, folder):

	if not os.path.exists(folder):
		os.makedirs(folder)

	for i in chr_map:
		i = ord(i)
		font = ImageFont.truetype(font_name, size-3)

		canvas = Image.new('RGB', (size, size), "white")

		draw = ImageDraw.Draw(canvas)
		draw.fontmode = "1"
		draw.text((2,0), chr(i), 'black', font)

		canvas.save(folder + "/" + chr(i)+".bmp", "BMP")


def generatefont_external(font_name):
	pass



sys.argv.pop(0)
if len(sys.argv) > 0:
	if sys.argv[0] == "image":
		if len(sys.argv) == 3:
			var_name = (sys.argv[2])
			convert_image(sys.argv[1], var_name)

		elif len(sys.argv) == 2:
			convert_image(sys.argv[1], (sys.argv[1].split("."))[0])

	if sys.argv[0] == "font":
		if len(sys.argv) == 3:
			var_name = sys.argv[2]
			convert_font(sys.argv[1], var_name)

	if sys.argv[0] == "gen-font":
		print("efec")
		if len(sys.argv) == 4:
		    generatefont_internal(sys.argv[1], int(sys.argv[2]), sys.argv[3])
