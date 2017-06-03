cc = gcc
FILE = src/
OBJFILE = bin/
CFLAGS = -std=c99 -Wall -g -pedantic
EXE = run

all: $(EXE)

$(EXE): main.o north.o east.o south.o west.o BIN OBJ
	gcc main.o north.o east.o south.o west.o -o ./bin/$(EXE)

BIN:
	if [ ! -d "bin" ]; then mkdir bin; fi;

OBJ:
	if [ ! -d "obj" ]; then mkdir obj; fi;

cppcheck:
	cppcheck --enable=all --language=c --std=c99 --inconclusive --suppress=missingInclude src/*.c -i ./include

main.o: ./src/main.c
	$(CC) -c $(CFLAGS) ./src/main.c -I./include

north.o: ./src/north.c
	$(CC) -c $(CFLAGS) ./src/north.c -I./include

east.o: ./src/east.c
	$(CC) -c $(CFLAGS) ./src/east.c -I./include

south.o: ./src/south.c
	$(CC) -c $(CFLAGS) ./src/south.c -I./include

west.o: ./src/west.c
	$(CC) -c $(CFLAGS) ./src/west.c -I./include

doxy: Doxyfile
	doxygen

test: ./src/functions.o BIN
	gcc functions.o -o ./bin/test

clean:
	rm *.o
