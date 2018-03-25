CC = gcc
FILE = src/
OBJFILE = bin/
CFLAGS = -std=c99 -Wall -g -pedantic
EXE1 = dine
EXE2 = holes

all: $(EXE1) $(EXE2)

$(EXE1): BIN OBJ dine.o 
	gcc ./obj/dine.o -o ./bin/$(EXE1) -lpthread

$(EXE2): BIN OBJ holes.o LinkedListAPI.o
	$(CC) ./obj/holes.o ./obj/LinkedListAPI.o -o ./bin/$(EXE2)

BIN:
	if [ ! -d "bin" ]; then mkdir bin; fi;

OBJ:
	if [ ! -d "obj" ]; then mkdir obj; fi;

dine.o: ./src/dine.c
	$(CC) -c $(CFLAGS) $(FILE)dine.c -I./include -o ./obj/dine.o

holes.o: ./src/holes.c
	$(CC) -c $(CFLAGS) $(FILE)holes.c -I./include -o ./obj/holes.o

LinkedListAPI.o: ./src/LinkedListAPI.c
	$(CC) -c $(CFLAGS) ./src/LinkedListAPI.c -I./include -o ./obj/LinkedListAPI.o


clean:
	rm -rf bin obj