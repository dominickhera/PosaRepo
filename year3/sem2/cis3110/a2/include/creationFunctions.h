#ifndef __DHERA_CREATIONFUNCTIONS__
#define __DHERA_CREATIONFUNCTIONS__

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "simcpu.h"
#include "LinkedListAPI.h"

typedef struct 
{

	int threadSwitch;
	int processSwitch;
	List processes;

}simSystem;

typedef struct 
{

	List threads;

}process;

typedef struct
{

	int arrivalTime;
	int serviceTime;
	int threadIOTime;
	int turnaroundTime;
	int threadFinishTime;
	List bursts;

}thread;

typedef struct
{

	int cpuTime;
	int ioTime;
	
}burst;

simSystem * initializeSimSystem(int threadSwitch, int processSwitch);
process * initializeProcess();
thread * initializeThread(int arrivalTime);
burst * initializeBurst(int cpuTime, int ioTime);
int compareData(const void* first,const void* second);
char* printGivenData(void* toBePrinted);

#endif