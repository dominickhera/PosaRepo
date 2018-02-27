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
    tempSystem->simTime = 0;
    tempSystem->busyFlag = 0;
    tempSystem->verboseFlag = 0;
    tempSystem->detailFlag = 0;
    tempSystem->quantumInteger = 0;
    tempSystem->rrFlag = 0;
    tempSystem->threadSwitch = threadSwitch;
    tempSystem->processSwitch = processSwitch;
    tempSystem->processes = initializeList(printGivenData, &free, compareData);
    tempSystem->readyProcesses = initializeList(printGivenData, &free, compareData);
    tempSystem->terminatedProcesses = initializeList(printGivenData, &free, compareData);
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

thread * initializeThread(int arrivalTime, char* state)
{

    thread * tempThread = malloc(sizeof(thread));
    tempThread->state = malloc(sizeof(state) * 64);
    strcpy(tempThread->state, state);
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
    printf("At time %d: Thread %d of Process %d moves from %s to %s\n", timeNum, threadNum, processNum, currentState, newState);
}

void detailPrint(int threadNum, int processNum, int arrivalTime, int serviceTime, int ioTime, int turnaroundTime, int finishTime)
{
    printf("Thread %d of Process %d:\n\narrival time: %d\nservice time: %d\nunits I/O time: %d\nunits turnaround time: %d\nunits finish time: %d\n", threadNum, processNum, arrivalTime, serviceTime, ioTime, turnaroundTime, finishTime);
}

void finishPrint(int scheduleType, int quantumInteger, int totalTime, int turnaroundTime, int cpuUtilization)
{
    if(scheduleType == 0)
    {
        printf("Round Robin (quantum = %d time units):\n\n", quantumInteger);

    }
    else
    {
        printf("FCFS:\n\n");
    }

    printf("Total Time required is %d time units\nAverage Turnaround Time is %d time units\n CPU Utilization is %d%%\n", totalTime, turnaroundTime, cpuUtilization);
    // FCFS:
    // Total Time required is 344 time units Average Turnaround Time is 27.9 time units CPU Utilization is 94%
}

int averageTurnAroundTimeCalc(List * threadList)
{
    int averageTime = 0;
    int totalTime = 0;
    int count = 0;

    if(threadList != NULL)
    {
        process * tempThreadList = (process*)threadList;
        if(getLength(tempThreadList->threads)!= 0)
        {
            void* elem;
            ListIterator elemIter = createIterator(tempThreadList->threads);
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

// int cpuUtilizationCalc()
// {
// 	return 0;
// }

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

void FCFSSim(simSystem * simSystem)
{
    moveProcessReady(simSystem, simSystem->verboseFlag, simSystem->detailFlag);

    while(getLength(simSystem->readyProcesses) != 0 || getLength(simSystem->runningProcesses) != 0 || getLength(simSystem->waitingProcesses) != 0 || getLength(simSystem->terminatedProcesses) != 0)
    {
        FCFSProcessRun(simSystem);
        simSystem->simTime++;
    }
}

void moveProcessReady(simSystem * simSystem, int verboseFlag, int detailFlag)
{
    int tempThreadCount = 1;
    int tempProcessCount = 1;
    void* processElem;
    ListIterator processElemIter = createIterator(simSystem->processes);
    while((processElem = nextElement(&processElemIter)) != NULL)
    {
        process * tempProcess = (process*)processElem;
        process * newProcess = initializeProcess();
        tempThreadCount = 1;
        void* threadElem;
        ListIterator threadElemIter = createIterator(tempProcess->threads);
        while((threadElem = nextElement(&threadElemIter)) != NULL)
        {
            thread * tempThread = (thread*)threadElem;
            thread * newThread = initializeThread(tempThread->arrivalTime, "ready");
            void* burstElem;
            ListIterator burstElemIter = createIterator(tempThread->bursts);
            while((burstElem = nextElement(&burstElemIter)) != NULL)
            {
                burst * tempBurst = (burst*)burstElem;
                burst * newBurst = initializeBurst(tempBurst->cpuTime, tempBurst->ioTime);
                insertBack(&newThread->bursts, newBurst);
            }if(verboseFlag == 1)
            {
    //             // verbosePrint(int timeNum, int threadNum, int processNum, char* currentState, char* newState)
                verbosePrint(simSystem->simTime, tempThreadCount, tempProcessCount, tempThread->state, newThread->state);
            }
            insertBack(&newProcess->threads, newThread);
            tempThreadCount++;
        }

        insertBack(&simSystem->readyProcesses, newProcess);
        tempProcessCount++;
    }
    

}

void moveProcessRunning(simSystem * simSystem, int verboseFlag, int detailFlag)
{
    int tempThreadCount = 1;
    int tempProcessCount = 1;
    void* processElem;
    ListIterator processElemIter = createIterator(simSystem->readyProcesses);
    while((processElem = nextElement(&processElemIter)) != NULL)
    {
        process * tempProcess = (process*)processElem;
        process * newProcess = initializeProcess();
        tempThreadCount = 1;
        void* threadElem;
        ListIterator threadElemIter = createIterator(tempProcess->threads);
        while((threadElem = nextElement(&threadElemIter)) != NULL)
        {
            thread * tempThread = (thread*)threadElem;
            thread * newThread = initializeThread(tempThread->arrivalTime, "running");
            void* burstElem;
            ListIterator burstElemIter = createIterator(tempThread->bursts);
            while((burstElem = nextElement(&burstElemIter)) != NULL)
            {
                burst * tempBurst = (burst*)burstElem;
                burst * newBurst = initializeBurst(tempBurst->cpuTime, tempBurst->ioTime);
                newBurst->startTime = simSystem->simTime;
                insertBack(&newThread->bursts, newBurst);
                deleteDataFromList(&tempThread->bursts, tempBurst);
            }if(verboseFlag == 1)
            {
    //             // verbosePrint(int timeNum, int threadNum, int processNum, char* currentState, char* newState)
                verbosePrint(simSystem->simTime, tempThreadCount, tempProcessCount, tempThread->state, newThread->state);
            }
            insertBack(&newProcess->threads, newThread);
            deleteDataFromList(&tempProcess->threads, tempThread);
            tempThreadCount++;
        }

        insertBack(&simSystem->runningProcesses, newProcess);
        deleteDataFromList(&simSystem->readyProcesses, tempProcess);
        tempProcessCount++;
    }

}

void FCFSProcessRun(simSystem * simSystem)
{

    if(getLength(simSystem->runningProcesses) != 0)
    {
        int timeInt = 0;
        ListIterator elemIter = createIterator(simSystem->runningProcesses);
        process * tempProcess = (process*)elemIter;
        ListIterator processIter = createIterator(tempProcess->threads);
        thread * tempThread = (thread*)processIter;
        ListIterator threadIter = createIterator(tempThread->threads);
        burst * tempBurst = (burst*)threadIter;

        timeInt = tempBurst->cpuTime - (simSystem->simTime - tempBurst->startTime);
        simSystem->busyFlag = 1;
    }
    else
    {

        if(simSystem->busyFlag == 1)
        {

        }
        else
        {
            moveProcessRunning(simSystem, simSystem->verboseFlag, simSystem->detailFlag);
        }

    }


}

// void RRProcessRun()
// {

// }




