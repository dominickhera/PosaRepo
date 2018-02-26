// #include <stdio.h>
// #include <string.h>
// #include <ctype.h>
// #include <stdlib.h>
// #include "simcpu.h"
#include "creationFunctions.h"
// #include "LinkedListAPI.h"


simSystem * initializeSimSystem(int threadSwitch, int processSwitch)
{

	simSystem * tempSystem = malloc(sizeof(simSystem));
	tempSystem->threadSwitch = threadSwitch;
	tempSystem->processSwitch = processSwitch;
	tempSystem->processes = initializeList(printGivenData, &free, compareData);

	return tempSystem;
}

process * initializeProcess()
{

	process * tempProcess = malloc(sizeof(process));
	tempProcess->threads = initializeList(printGivenData, &free, compareData);

	return tempProcess;

}

thread * initializeThread(int arrivalTime)
{

	thread * tempThread = malloc(sizeof(thread));
	tempThread->arrivalTime = arrivalTime;
	tempThread->serviceTime = 0;
	tempThread->threadIOTime = 0;
	tempThread->turnaroundTime = 0;
	tempThread->threadFinishTime = 0;
	tempThread->bursts = initializeList(printGivenData, &free, compareData);

	return tempThread;

}

burst * initializeBurst(int cpuTime, int ioTime)
{

	burst * tempBurst = malloc(sizeof(burst));
	tempBurst->cpuTime = cpuTime;
	tempBurst->ioTime = ioTime;

	return tempBurst;
}


int compareData(const void* first,const void* second)
{
    return strcmp((char*)first, (char*)second);
}

char* printGivenData(void* toBePrinted)
{
    if(toBePrinted!=NULL)
    {

        return (char *)toBePrinted;
    }
    return NULL;
}


