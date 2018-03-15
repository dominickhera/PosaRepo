cc = gcc
FILE = src/
OBJFILE = bin/
CFLAGS = -std=c11 -Wall -g -pedantic
EXE = run
LIBS = -L/usr/local/lib -lm -lliblist -llibcparse



all: $(EXE)

$(EXE): BIN OBJ GEDCOMparser.o LinkedListAPI.o listLib parserLib

BIN:
	if [ ! -d "bin" ]; then mkdir bin; fi;

OBJ:
	if [ ! -d "obj" ]; then mkdir obj; fi;

cppcheck:
	cppcheck --enable=all --language=c --std=c99 --inconclusive --suppress=missingInclude src/*.c -i ./include

GEDCOMparser.o: ./src/GEDCOMparser.c
	$(CC) -c $(CFLAGS) ./src/GEDCOMparser.c -I./include -o ./obj/GEDCOMparser.o

LinkedListAPI.o: ./src/LinkedListAPI.c
	$(CC) -c $(CFLAGS) ./src/LinkedListAPI.c -I./include -o ./obj/LinkedListAPI.o

parserLib: 
	$(CC) $(CFLAGS) -shared -o ./bin/parseLib.so -fPIC ./obj/GEDCOMparser.o ./obj/LinkedListAPI.o

listLib:
	$(CC) $(CFLAGS) -shared -o ./bin/listLib.so -fPIC ./obj/LinkedListAPI.o

clean:
	rm -rf bin obj
	