#ifndef _DHERA_FUNCTIONS_
#define _DHERA_FUNCTIONS_

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "heap.h"

void printData(void * data);
int compareFunction(const void *first,const void *second);
void reheapifyMax(Heap * heap, Node * newNode);
void reheapifyMin(Heap * heap, Node * newNode);

#endif
