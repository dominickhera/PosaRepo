cc = gcc
FILE = src/
OBJFILE = bin/
CFLAGS = -std=c11 -Wall -g -pedantic
EXE = test

all: $(EXE)

$(EXE): BIN OBJ Main.o CalendarParser.o LinkedListAPI.o
	gcc ./obj/Main.o ./obj/CalendarParser.o ./obj/LinkedListAPI.o -o $(OBJFILE)$(EXE)1

BIN:
	if [ ! -d "bin" ]; then mkdir bin; fi;

OBJ:
	if [ ! -d "obj" ]; then mkdir obj; fi;

cppcheck:
	cppcheck --enable=all --language=c --std=c99 --inconclusive --suppress=missingInclude src/*.c -i ./include

Main.o: ./src/Main.c
	$(CC) -c $(CFLAGS) ./src/Main.c -I./include -o ./obj/Main.o

CalendarParser.o: ./src/CalendarParser.c
	$(CC) -c $(CFLAGS) ./src/CalendarParser.c -I./include -o ./obj/CalendarParser.o

LinkedListAPI.o: ./src/LinkedListAPI.c
	$(CC) -c $(CFLAGS) ./src/LinkedListAPI.c -I./include -o ./obj/LinkedListAPI.o


clean:
	rm -rf bin obj
