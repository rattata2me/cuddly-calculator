
# gcc is ok for this
CC = gcc
CCW = i686-w64-mingw32-gcc

INCLUDE_DIRECTORY = include
SOURCE_DIRECTORY = source
BUILD_DIRECTORY = build

CFLAGS = -I$(INCLUDE_DIRECTORY) -g -Wall -pedantic -Werror

_OBJECT_FILES = main.o mathinterpreter.o
OBJ = $(patsubst %,$(BUILD_DIRECTORY)/%,$(_OBJECT_FILES))

LIBS = -lm

all: main



.PHONY: makebuild

makebuild: 
	@mkdir -p build

$(BUILD_DIRECTORY)/%.o: $(SOURCE_DIRECTORY)/%.c makebuild
	$(CC) -c -o $@ $< $(CFLAGS)


main: $(OBJ)
	$(CC) -o $(BUILD_DIRECTORY)/$@ $^ $(CFLAGS) $(LIBS)
	@echo Executable successfully compiled!


.PHONY: clean

clean:
	rm -f $(BUILD_DIRECTORY)/*.o $(BUILD_DIRECTORY)/main 


