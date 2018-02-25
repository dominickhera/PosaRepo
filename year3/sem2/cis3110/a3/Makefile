CC = gcc
FILE = src/
OBJFILE = bin/
CFLAGS = -std=c99 -Wall -g -pedantic
EXE1 = dine
EXE2 = holes

all: $(EXE1) $(EXE2)

$(EXE1): dine.o BIN
	gcc dine.o -o ./bin/$(EXE1) -lpthread

$(EXE2): holes.o BIN
	$(CC) holes.o -o ./bin/$(EXE2)

BIN:
	if [ ! -d "bin" ]; then mkdir bin; fi;

dine.o: ./src/dine.c
	$(CC) -c $(CFLAGS) ./src/dine.c -Iinclude

holes.o: ./src/holes.c
	$(CC) -c $(CFLAGS) ./src/holes.c -Iinclude

clean:
	rm *.o