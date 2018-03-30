cc = gcc
FILE = src/
OBJFILE = bin/
CFLAGS = -std=c11 -Wall -g -pedantic
EXE = run
LIBS = -L/usr/local/lib -lm -lliblist -llibcparse

all: $(EXE)

$(EXE): BIN OBJ list parser
	ar cr ./bin/liblist.a ./obj/LinkedListAPI.o ;\
	ar cr ./bin/libcparse.a ./obj/GEDCOMparser.o ./obj/LinkedListAPI.o

test: BIN OBJ Main.o GEDCOMparser.o LinkedListAPI.o
	gcc ./obj/Main.o ./obj/GEDCOMparser.o ./obj/LinkedListAPI.o $(CFLAGS) -o  $(OBJFILE)TEST

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


list: BIN OBJ LinkedListAPI.o
	ar cr ./bin/liblist.a ./obj/LinkedListAPI.o

parser: BIN OBJ GEDCOMparser.o LinkedListAPI.o
	ar cr ./bin/libcparse.a ./obj/GEDCOMparser.o ./obj/LinkedListAPI.o

clean:
	rm -rf bin obj