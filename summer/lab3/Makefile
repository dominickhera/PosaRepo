cc = gcc
FILE = src/
OBJFILE = bin/
CFLAGS = -std=c99 -Wall -g -pedantic
EXE = run

all: $(EXE)

$(EXE): main.o heap.o functions.o BIN OBJ
	gcc main.o heap.o functions.o -o ./bin/$(EXE)

BIN:
	if [ ! -d "bin" ]; then mkdir bin; fi;

OBJ:
	if [ ! -d "obj" ]; then mkdir obj; fi;

cppcheck:
	cppcheck --enable=all --language=c --std=c99 --inconclusive --suppress=missingInclude src/*.c -i ./include

main.o: ./src/main.c
	$(CC) -c $(CFLAGS) ./src/main.c -I./include

heap.o: ./src/heap.c
	$(CC) -c $(CFLAGS) ./src/heap.c -I./include

functions.o: ./src/functions.c
	$(CC) -c $(CFLAGS) ./src/functions.c -I./include

doxy: Doxyfile
	doxygen

clean:
	rm *.o
