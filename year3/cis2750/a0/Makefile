cc = gcc
FILE = src/
OBJFILE = bin/
CFLAGS = -std=c11 -Wall
EXE = test

all: $(EXE)1

$(EXE)1: BIN OBJ StructListDemo.o LinkedListAPI.o
	gcc ./obj/StructListDemo.o ./obj/LinkedListAPI.o -o $(OBJFILE)$(EXE)1

$(EXE)2: BIN OBJ StringListDemo.o LinkedListAPI.o
	gcc ./obj/StringListDemo.o ./obj/LinkedListAPI.o -o $(OBJFILE)$(EXE)2

BIN:
	if [ ! -d "bin" ]; then mkdir bin; fi;

OBJ:
	if [ ! -d "obj" ]; then mkdir obj; fi;

cppcheck:
	cppcheck --enable=all --language=c --std=c99 --inconclusive --suppress=missingInclude src/*.c -i ./include

StructListDemo.o: ./src/StructListDemo.c
	$(CC) -c $(CFLAGS) ./src/StructListDemo.c -I./include -o ./obj/StructListDemo.o

StringListDemo.o: ./src/StringListDemo.c
	$(CC) -c $(CFLAGS) ./src/StringListDemo.c -I./include -o ./obj/StringListDemo.o

LinkedListAPI.o: ./src/LinkedListAPI.c
	$(CC) -c $(CFLAGS) ./src/LinkedListAPI.c -I./include -o ./obj/LinkedListAPI.o


clean:
	rm -rf bin obj
