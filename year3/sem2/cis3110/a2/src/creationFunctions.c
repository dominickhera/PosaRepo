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
	tempSystem->runningProcesses = initializeList(printGivenData, &free, compareData);
	tempSystem->waitingProcesses = initializeList(printGivenData, &free, compareData);

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
	tempThread->state = malloc(sizeof(char) * 64);
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
	tempBurst->startTime = 0;

	return tempBurst;
}

void verbosePrint(int timeNum, int threadNum, int processNum, char* currentState, char* newState)
{
	printf(" At time %d: Thread %d of Process %d moves from %s to %s\n", timeNum, threadNum, processNum, currentState, newState);
}

void detailPrint(int threadNum, int processNum, int arrivalTime, int serviceTime, int ioTime, int turnaroundTime, int finishTime)
{
	printf("Thread %d of Process %d:\n\narrival time: %d\nservice time: %d\nunits I/O time: %d\nunits turnaround time: %d\nunits finish time: %d\n", threadNum, processNum, arrivalTime, serviceTime, ioTime, turnaroundTime, finishTime);
}

void finishPrint(int scheduleType, int quantumInteger)
{
	if(scheduleType == 0)
	{
		printf("Round Robin (quantum = %d time units):\n\n", quantumInteger);

	}
	else
	{
		printf("FCFS:\n\n");
	}

	printf("Total Time required is %d time units\nAverage Turnaround Time is %d time units\n CPU Utilization is %d%%\n");
	// FCFS:
// Total Time required is 344 time units Average Turnaround Time is 27.9 time units CPU Utilization is 94%
}

int averageTurnAroundTimeCalc(List * threadList)
{
	int averageTime = 0;
	int totalTime = 0;
	int count = 0;

	if(threadsList != NULL)
	{
		if(threadList->threads != NULL)
		{
			void* elem;
			ListIterator elemIter = createIterator(threadList->threads);
			while((elem = nextElement(&elemIter)) != NULL)
			{
				thread * tempThread = (thread*)elem;
				totalTime += tempThread->turnaroundTime;
				count++;
			}

			averageTime = (totalTime / count);
		}
	}

	return averageTime;
}

int cpuUtilizationCalc()
{
	return 0;
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


