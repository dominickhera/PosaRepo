#ifndef _DHERA_FUNCTIONS_
#define _DHERA_FUNCTIONS_

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "HashTableAPI.h"

void printData(void * data);
int hashData(size_t hashSize, char * dataKey);
void getPos(int *, int *);

#endif
