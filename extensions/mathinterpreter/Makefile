
# gcc is ok for this
CC = gcc

OBJ = main.o


INCLUDE_DIRECTORY = include
SOURCE_DIRECTORY = source
BUILD_DIRECTORY = build


CFLAGS = -I$(IDIR) -g -Wall

_HEADER_FILES = common.h
HEADER_FILES = $(patsubst %,$(INCLUDE_DIRECTORY)/%,$(_HEADER_FILES))

_OBJECT_FILES = main.o
OBJ = $(patsubst %,$(BUILD_DIRECTORY)/%,$(_OBJECT_FILES))

LIBS = 


$(BUILD_DIRECTORY)/%.o: $(SOURCE_DIRECTORY)/%.c $(HEADER_FILES)
	$(CC) -c -o $@ $< $(CFLAGS)


main: $(OBJ)
	$(CC) -o $(BUILD_DIRECTORY)/$@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -f $(BUILD_DIRECTORY)/*.o 


