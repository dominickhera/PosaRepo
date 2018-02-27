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
	int busyFlag;
	int simTime;
	int verboseFlag;
	int detailFlag;
	int quantumInteger;
	int rrFlag;
	List processes;
	List readyProcesses;
	List runningProcesses;
	List waitingProcesses;
	List terminatedProcesses;

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
	char *state;
	List bursts;

}thread;

typedef struct
{
	int startTime;
	int cpuTime;
	int ioTime;
	
}burst;

simSystem * initializeSimSystem(int threadSwitch, int processSwitch);
process * initializeProcess();
thread * initializeThread(int arrivalTime, char* state);
burst * initializeBurst(int cpuTime, int ioTime);
int compareData(const void* first,const void* second);
char* printGivenData(void* toBePrinted);
void verbosePrint(int timeNum, int threadNum, int processNum, char* currentState, char* newState);
void detailPrint(int threadNum, int processNum, int arrivalTime, int serviceTime, int ioTime, int turnaroundTime, int finishTime);
void finishPrint(int scheduleType, int quantumInteger, int totalTime, int turnaroundTime, int cpuUtilization);
int averageTurnAroundTimeCalc(List * threadList);
void moveProcessReady(simSystem * simSystem, int verboseFlag, int detailFlag);
void moveProcessRunning(simSystem * simSystem, int verboseFlag, int detailFlag);
void FCFSProcessRun(simSystem * simSystem);
void FCFSSim(simSystem * simSystem);


#endif
