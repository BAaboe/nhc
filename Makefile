CC=  g++  # gcc or g++
WINCC= i686-w64-mingw32-gcc

CFLAGS=-g -Wall
LIBS=-lraylib -ljsoncpp

O=./build
S=./src

OBJS=				\
			$(O)/player.o \
			$(O)/menu.o \
			$(O)/credits.o \

all:	 $(O)/nhc

clean:
	rm -f ./build/*.o

run: all
	./nhc

$(O)/nhc:	$(OBJS) $(O)/main.o
	$(CC) $(CFLAGS) $(OBJS) $(O)/main.o \
	-o nhc $(LIBS)

$(O)/%.o:	$(S)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@
