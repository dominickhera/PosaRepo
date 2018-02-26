CC = gcc
FILE = src/
OBJFILE = bin/
CFLAGS = -std=c99 -Wall -g -pedantic
EXE = simcpu 


all: $(EXE)

$(EXE): BIN OBJ simcpu.o creationFunctions.o LinkedListAPI.o 
	$(CC) ./obj/simcpu.o ./obj/creationFunctions.o ./obj/LinkedListAPI.o -o ./bin/$(EXE)

BIN:
	if [ ! -d "bin" ]; then mkdir bin; fi;

OBJ:
	if [ ! -d "obj" ]; then mkdir obj; fi;

simcpu.o: ./src/simcpu.c
	$(CC) -c $(CFLAGS) $(FILE)simcpu.c -I./include -o ./obj/simcpu.o

creationFunctions.o: ./src/creationFunctions.c
	$(CC) -c $(CFLAGS) $(FILE)creationFunctions.c -I./include -o ./obj/creationFunctions.o

LinkedListAPI.o: ./src/LinkedListAPI.c
	$(CC) -c $(CFLAGS) ./src/LinkedListAPI.c -I./include -o ./obj/LinkedListAPI.o

		
clean:
	rm -rf bin obj

# cc = gcc
# FILE = src/
# OBJFILE = bin/
# CFLAGS = -std=c11 -Wall -g -pedantic
# EXE = run
# LIBS = -L/usr/local/lib -lm -lliblist -llibcparse

# all: $(EXE)

# $(EXE): BIN OBJ list parser
# 	ar cr ./bin/liblist.a ./obj/LinkedListAPI.o ;\
# 	ar cr ./bin/libcparse.a ./obj/GEDCOMparser.o ./obj/LinkedListAPI.o

# BIN:
# 	if [ ! -d "bin" ]; then mkdir bin; fi;

# OBJ:
# 	if [ ! -d "obj" ]; then mkdir obj; fi;

# cppcheck:
# 	cppcheck --enable=all --language=c --std=c99 --inconclusive --suppress=missingInclude src/*.c -i ./include

# GEDCOMparser.o: ./src/GEDCOMparser.c
# 	$(CC) -c $(CFLAGS) ./src/GEDCOMparser.c -I./include -o ./obj/GEDCOMparser.o

# LinkedListAPI.o: ./src/LinkedListAPI.c
# 	$(CC) -c $(CFLAGS) ./src/LinkedListAPI.c -I./include -o ./obj/LinkedListAPI.o


# list: BIN OBJ LinkedListAPI.o
# 	ar cr ./bin/liblist.a ./obj/LinkedListAPI.o

# parser: BIN OBJ GEDCOMparser.o LinkedListAPI.o
# 	ar cr ./bin/libcparse.a ./obj/GEDCOMparser.o ./obj/LinkedListAPI.o

# clean:
# 	rm -rf bin obj
