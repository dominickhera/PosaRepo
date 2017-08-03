cc = gcc
FILE = src/
OBJFILE = bin/
CFLAGS = -std=c99 -Wall -g -pedantic
EXE = run

all: $(EXE)

$(EXE): BIN OBJ main.o tree.o balancedTreeAPI.o HashTableAPI.o LinkedListAPI.o
	gcc ./obj/main.o ./obj/tree.o ./obj/balancedTreeAPI.o ./obj/HashTableAPI.o ./obj/LinkedListAPI.o -o $(OBJFILE)$(EXE)

BIN:
	if [ ! -d "bin" ]; then mkdir bin; fi;

OBJ:
	if [ ! -d "obj" ]; then mkdir obj; fi;

cppcheck:
	cppcheck --enable=all --language=c --std=c99 --inconclusive --suppress=missingInclude src/*.c -i ./include

main.o: ./src/main.c
	$(CC) -c $(CFLAGS) ./src/main.c -I./include -o ./obj/main.o

tree.o: ./src/tree.c
	$(CC) -c $(CFLAGS) ./src/tree.c -I./include -o ./obj/tree.o

balancedTreeAPI.o: ./src/balancedTreeAPI.c
	$(CC) -c $(CFLAGS) ./src/balancedTreeAPI.c -I./include -o ./obj/balancedTreeAPI.o

HashTableAPI.o: ./src/HashTableAPI.c
	$(CC) -c $(CFLAGS) ./src/HashTableAPI.c -I./include -o ./obj/HashTableAPI.o

LinkedListAPI.o: ./src/HashTableAPI.c
	$(CC) -c $(CFLAGS) ./src/LinkedListAPI.c -I./include -o ./obj/LinkedListAPI.o

doxy: Doxyfile
	doxygen

clean:
	rm -rf bin obj
