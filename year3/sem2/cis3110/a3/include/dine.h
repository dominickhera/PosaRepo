#ifndef __DHERA_DINE__
#define __DHERA_DINE__

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

void *philosopherFunction(void* position);
void eat(int eatPosition);
void think(int thinkPosition);

#endif
