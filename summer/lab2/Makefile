cc = gcc
FILE = src/
OBJFILE = bin/
CFLAGS = -std=c99 -Wall -g -pedantic
EXE = run

all: $(EXE)

$(EXE): main.o HashTableAPI.o BIN OBJ
	gcc main.o HashTableAPI.o -o ./bin/$(EXE)

BIN:
	if [ ! -d "bin" ]; then mkdir bin; fi;

OBJ:
	if [ ! -d "obj" ]; then mkdir obj; fi;

cppcheck:
	cppcheck --enable=all --language=c --std=c99 --inconclusive --suppress=missingInclude src/*.c -i ./include

main.o: ./src/main.c
	$(CC) -c $(CFLAGS) ./src/main.c -I./include

HashTableAPI.o: ./src/HashTableAPI.c
	$(CC) -c $(CFLAGS) ./src/HashTableAPI.c -I./include

doxy: Doxyfile
	doxygen

test: ./src/functions.o BIN
	gcc functions.o -o ./bin/test

clean:
	rm *.o
