
# gcc is ok for this
CC = gcc


INCLUDE_DIRECTORY = include
LIBRARY_DIRECTORY = ../../extensions/graphics/build
INCLUDE_LIBRARY =  ../../extensions/graphics/include 
IMAGES_DIRECTORY = ../../extensions/graphics/images
SOURCE_DIRECTORY = source
BUILD_DIRECTORY = build

GRAPHICS = SDL_SIM

CFLAGS = -I$(INCLUDE_DIRECTORY) -I$(INCLUDE_LIBRARY) -I$(IMAGES_DIRECTORY) -g -Wall -Werror -pedantic  -D $(GRAPHICS)

_OBJECT_FILES = main.o

LIBS = `sdl2-config --cflags --libs` -lSDL2 

ifeq ($(GRAPHICS), SDL_SIM)
	_OBJECT_FILES += sdl_window.o
endif

ifeq ($(GRAPHICS), NCURSES_SIM)
	LIBS = -lncurses
	_OBJECT_FILES += ncurses_window.o
endif

MI_LIBRARY = ../../extensions/mathinterpreter/build

LIBS += -L$(LIBRARY_DIRECTORY) -lcalcg -L$(MI_LIBRARY) -lmi -lm

OBJ = $(patsubst %,$(BUILD_DIRECTORY)/%,$(_OBJECT_FILES))

all: main

.PHONY: makebuild

makebuild: 
	@mkdir -p build
	@mkdir -p build
	@mkdir -p build

library:
	cd $(LIBRARY_DIRECTORY)/.. && make all

$(BUILD_DIRECTORY)/%.o: $(SOURCE_DIRECTORY)/%.c makebuild library
	$(CC) -c -o $@ $< $(CFLAGS)
	

main: $(OBJ)
	$(CC) -o $(BUILD_DIRECTORY)/$@ $^ $(CFLAGS) $(LIBS)
	@echo Executable successfully compiled!

.PHONY: clean
clean:
	rm -f $(BUILD_DIRECTORY)/*.o $(BUILD_DIRECTORY)/main 
	@cd $(LIBRARY_DIRECTORY) && cd .. && make clean



