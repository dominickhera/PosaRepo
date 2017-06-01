cc = gcc
FILE = src/
OBJFILE = bin/
CFLAGS = -std=c99 -Wall -g -pedantic
EXE = run

all: $(EXE)

$(EXE): LinkedListAPI.o BIN
	gcc LinkedListAPI.o -o ./bin/$(EXE)

BIN:
	if [ ! -d "bin" ]; then mkdir bin; fi;

cppcheck:
	cppcheck --enable=all --language=c --std=c99 --inconclusive --suppress=missingInclude src/*.c -i ./include

LinkedListAPI.o: ./src/LinkedListAPI.c
	$(CC) -c $(CFLAGS) ./src/LinkedListAPI.c -Iinclude

doxy: Doxyfile
	doxygen

test: ./src/parse.o BIN
	gcc parse.o -o ./bin/test

clean:
	rm *.o
