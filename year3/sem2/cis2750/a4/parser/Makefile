cc = gcc
FILE = src/
OBJFILE = bin/
CFLAGS = -std=c11 -Wall -g -pedantic
EXE = run
# LIBS = -L/usr/local/lib -lm -lliblist -llibcparse

UNAME_S := $(shell uname -s)

# # OS X Dependant Variables
ifeq ($(UNAME_S), Darwin)
    LIB := parserLib.dylib
    LISTLIB := listLib.dylib
# # GNU/Linux Depedant Variables
else ifeq ($(UNAME_S), Linux)
    LIB := parserLib.so
    LISTLIB := listLib.so
endif

# $(LIB): sharedLib.o
# 	$(CC) -shared -o $(LIB) sharedLib.o

# sharedLib.o: sharedLib.c
# 	$(CC) $(CFLAGS) -c -fpic sharedLib.c

# clean:
# 	rm $(LIB) *.o


all: $(EXE)

$(EXE): BIN OBJ GEDCOMparser.o LinkedListAPI.o $(LISTLIB) $(LIB)

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

$(LIB): 
	$(CC) $(CFLAGS) -shared -o ./bin/$(LIB) -fPIC ./obj/GEDCOMparser.o ./obj/LinkedListAPI.o

$(LISTLIB):
	$(CC) $(CFLAGS) -shared -o ./bin/$(LISTLIB) -fPIC ./obj/LinkedListAPI.o

clean:
	rm -rf bin obj
