
# gcc is ok for this
CC = gcc


INCLUDE_DIRECTORY = include
SOURCE_DIRECTORY = source
IMAGES_DIRECTORY = images
BUILD_DIRECTORY = build


MI_LIBRARY = ../mathinterpreter/build
MI_INCLUDE = ../mathinterpreter/include

CFLAGS = -I$(INCLUDE_DIRECTORY) -I$(IMAGES_DIRECTORY) -I$(MI_INCLUDE) -g -Wall -Werror -pedantic -std=gnu11

_OBJECT_FILES = common.o graphics/pixelsurface.o graphics/renderer.o input.o math/vec2.o graphics/texture.o graphics/font.o
_OBJECT_FILES += math/rect.o graphics/ui.o programs/calc.o

OBJ = $(patsubst %,$(BUILD_DIRECTORY)/%,$(_OBJECT_FILES))

IMAGES := $(shell find $(IMAGES_DIRECTORY) -name '*.bmp')
IMAGES_OBJECT_FILES := $(subst .bmp,.o, $(IMAGES))
IMAGES_C_FILES := $(subst .bmp,.c, $(IMAGES))

all: mathinterpreter main

.PHONY: makebuild

makebuild:
	@mkdir -p build
	@mkdir -p build/graphics
	@mkdir -p build/math
	@mkdir -p build/programs

LIB_NAME = libcalcg.a

LIBS = -L$(MI_LIBRARY) -lmi

# Images auto generation

PYTHON = python
BMP2C = ../../tools/bmp2c/bmp2c.py

$(IMAGES_DIRECTORY)/%.c: $(IMAGES_DIRECTORY)/%.bmp
	$(PYTHON) $(BMP2C) image $<

$(IMAGES_DIRECTORY)/%.o: $(IMAGES_DIRECTORY)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(BUILD_DIRECTORY)/%.o: $(SOURCE_DIRECTORY)/%.c makebuild
	$(CC) -c -o $@ $< $(CFLAGS)


mathinterpreter:
	cd $(MI_LIBRARY)/.. && make all

main: $(IMAGES_OBJECT_FILES) $(OBJ)
	ar rcs $(BUILD_DIRECTORY)/$(LIB_NAME) $^
	@echo Library Succesfully compiled!!!

.PHONY: clean
clean:
	rm -f $(BUILD_DIRECTORY)/*.o $(BUILD_DIRECTORY)/main $(IMAGES_DIRECTORY)/*.c $(IMAGES_DIRECTORY)/*.h $(IMAGES_DIRECTORY)/*.o
