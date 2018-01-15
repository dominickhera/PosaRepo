CC = gcc
FILE = src/
OBJFILE = bin/
CFLAGS = -std=c99 -Wall -g -pedantic
EXE = simcpu 


all: $(EXE)

$(EXE): BIN simcpu.o 
	$(CC) simcpu.o -o ./bin/$(EXE)

BIN:
	if [ ! -d "bin" ]; then mkdir bin; fi;

simcpu.o: ./src/simcpu.c
	$(CC) -c $(CFLAGS) $(FILE)simcpu.c -Iinclude
		
clean:
	rm *.o
