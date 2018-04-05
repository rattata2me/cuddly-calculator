
# gcc is ok for this
CC = gcc


INCLUDE_DIRECTORY = include
SOURCE_DIRECTORY = source
BUILD_DIRECTORY = build


CFLAGS = -I$(INCLUDE_DIRECTORY) -g -Wall -pedantic -Werror

_HEADER_FILES = common.h graphics/pixelbuffer.h graphics/renderer.h math/vec2.h
HEADER_FILES = $(patsubst %,$(INCLUDE_DIRECTORY)/%,$(_HEADER_FILES))

_OBJECT_FILES = main.o common.o graphics/pixelbuffer.o graphics/renderer.o math/vec2.o
OBJ = $(patsubst %,$(BUILD_DIRECTORY)/%,$(_OBJECT_FILES))

LIBS = `sdl2-config --cflags --libs` -lSDL2 


all: main

.PHONY: makebuild

makebuild: 
	@mkdir -p build
	@mkdir -p build/graphics
	@mkdir -p build/math

$(BUILD_DIRECTORY)/%.o: $(SOURCE_DIRECTORY)/%.c $(HEADER_FILES) makebuild
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $(BUILD_DIRECTORY)/$@ $^ $(CFLAGS) $(LIBS)
	@echo Executable successfully compiled!

.PHONY: clean
clean:
	rm -f $(BUILD_DIRECTORY)/*.o $(BUILD_DIRECTORY)/main


