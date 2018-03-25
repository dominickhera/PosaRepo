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
	char processID[1];
	int processSize;
	int swapCount;

}Process;

Process * initializeProcess(char* processID, int processSize);
HoleSystem * initializeHoleSystem();
int compareData(const void* first,const void* second);
char* printGivenData(void* toBePrinted);
void firstFit(HoleSystem * holeSystem);
void swapProcess(HoleSystem * holeSystem);
void insertProcess(HoleSystem * holeSystem);
int checkBeginningHoleNum(HoleSystem * holeSystem);
int checkNextHoleSize(HoleSystem * holeSystem);
int checkHoleCount(HoleSystem * holeSystem);
int checkMemUsage(HoleSystem * HoleSystem);
void printProcessInfo(HoleSystem * holeSystem, Process * Process);
void printFinishedInfo(HoleSystem * holeSystem);


#endif
