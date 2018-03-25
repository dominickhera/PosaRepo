#ifndef __DHERA_HOLES__
#define __DHERA_HOLES__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "LinkedListAPI.h"

typedef struct
{
	char memory[127];
	int cumulativeMemUsage;
	int averageHoleCount;
	int averageProcessCount;
	List processes;
	List waitingProcesses;
	List runningProcesses;
	List completedProcesses;
}HoleSystem;


typedef struct 
{
	char * processID;
	int processSize;
	int swapCount;

}Process;

Process * initializeProcess(char* processID, int processSize);
HoleSystem * initializeHoleSystem();
int compareData(const void* first,const void* second);
char* printGivenData(void* toBePrinted);

#endif
