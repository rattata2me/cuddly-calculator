
# gcc is ok for this
CC = gcc


INCLUDE_DIRECTORY = include
SOURCE_DIRECTORY = source
IMAGES_DIRECTORY = images
BUILD_DIRECTORY = build


CFLAGS = -I$(INCLUDE_DIRECTORY) -I$(IMAGES_DIRECTORY) -g -Wall -pedantic -Werror

_OBJECT_FILES = main.o common.o graphics/pixelsurface.o graphics/renderer.o math/vec2.o graphics/texture.o
OBJ = $(patsubst %,$(BUILD_DIRECTORY)/%,$(_OBJECT_FILES))

IMAGES := $(shell find $(IMAGES_DIRECTORY) -name '*.bmp')
IMAGES_OBJECT_FILES := $(subst .bmp,.o, $(IMAGES))
IMAGES_C_FILES := $(subst .bmp,.c, $(IMAGES))

LIBS = `sdl2-config --cflags --libs` -lSDL2 


all: main

.PHONY: makebuild

makebuild: 
	@mkdir -p build
	@mkdir -p build/graphics
	@mkdir -p build/math


# Images auto generation

PYTHON = python
BMP2C = ../bmp2c/bmp2c.py

$(IMAGES_DIRECTORY)/%.c: $(IMAGES_DIRECTORY)/%.bmp
	$(PYTHON) $(BMP2C) image $<

$(IMAGES_DIRECTORY)/%.o: $(IMAGES_DIRECTORY)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(BUILD_DIRECTORY)/%.o: $(SOURCE_DIRECTORY)/%.c makebuild
	$(CC) -c -o $@ $< $(CFLAGS)
	

main: $(IMAGES_OBJECT_FILES) $(OBJ)
	$(CC) -o $(BUILD_DIRECTORY)/$@ $^ $(CFLAGS) $(LIBS)
	@echo Executable successfully compiled!

.PHONY: clean
clean:
	rm -f $(BUILD_DIRECTORY)/*.o $(BUILD_DIRECTORY)/main $(IMAGES_DIRECTORY)/*.c $(IMAGES_DIRECTORY)/*.h $(IMAGES_DIRECTORY)/*.o


