cc = gcc
FILE = src/
OBJFILE = bin/
CFLAGS = -std=c11 -Wall -g -pedantic
EXE = test

all: $(EXE)

$(EXE): BIN OBJ Main.o GEDCOMEparser.o LinkedListAPI.o
	gcc ./obj/Main.o ./obj/GEDCOMEparser.o ./obj/LinkedListAPI.o -o $(OBJFILE)$(EXE)1

BIN:
	if [ ! -d "bin" ]; then mkdir bin; fi;

OBJ:
	if [ ! -d "obj" ]; then mkdir obj; fi;

cppcheck:
	cppcheck --enable=all --language=c --std=c99 --inconclusive --suppress=missingInclude src/*.c -i ./include

Main.o: ./src/Main.c
	$(CC) -c $(CFLAGS) ./src/Main.c -I./include -o ./obj/Main.o

GEDCOMparser.o: ./src/GEDCOMparser.c
	$(CC) -c $(CFLAGS) ./src/GEDCOMparser.c -I./include -o ./obj/GEDCOMparser.o

LinkedListAPI.o: ./src/LinkedListAPI.c
	$(CC) -c $(CFLAGS) ./src/LinkedListAPI.c -I./include -o ./obj/LinkedListAPI.o


clean:
	rm -rf bin obj
