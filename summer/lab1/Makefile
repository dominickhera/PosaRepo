cc = gcc
FILE = src/
OBJFILE = bin/
CFLAGS = -std=c99 -Wall -g -pedantic
EXE = dLinkedList

all: $(EXE)

$(EXE): LinkedListAPI.o BIN
	gcc LinkedListAPI.o -o ./bin/$(EXE)

BIN:
	if [ ! -d "bin" ]; then mkdir bin; fi;

LinkedListAPI.o: ./src/LinkedListAPI.c
	$(CC) -c $(CFLAGS) ./src/LinkedListAPI.c -Iinclude

clean:
	rm *.o
