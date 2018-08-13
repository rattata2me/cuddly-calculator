
# gcc is ok for this
CC = gcc
CCW = i686-w64-mingw32-gcc

INCLUDE_DIRECTORY = include
SOURCE_DIRECTORY = source
BUILD_DIRECTORY = build

CFLAGS = -I$(INCLUDE_DIRECTORY) -g -Wall -pedantic -Werror

_OBJECT_FILES = mathinterpreter.o
OBJ = $(patsubst %,$(BUILD_DIRECTORY)/%,$(_OBJECT_FILES))

LIBS = -lm

all: main

LIB_NAME = libmi.a

.PHONY: makebuild

makebuild: 
	@mkdir -p build

$(BUILD_DIRECTORY)/%.o: $(SOURCE_DIRECTORY)/%.c makebuild
	$(CC) -c -o $@ $< $(CFLAGS)


main: $(OBJ)
	ar rcs $(BUILD_DIRECTORY)/$(LIB_NAME) $^
	@echo Library successfully compiled!


.PHONY: clean

clean:
	rm -f $(BUILD_DIRECTORY)/*.o $(BUILD_DIRECTORY)/*.a 


