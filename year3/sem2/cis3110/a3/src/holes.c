#include "holes.h"

int main(int argc, char **argv)
{

    if(argc != 2)
    {
        printf("not enough arguments, exiting...\n");
        exit(1);
    }

    FILE *fp;
    char line[256];
    char * p;
    char memoryValue[127][127];
    int memoryAmount[127];
    char * word;
    int count = 0;
    int parseCount = 0;

    fp = fopen(argv[1], "r");

    if(fp == NULL)
    {
        printf("couldn't find file\nexiting...\n");
        exit(1);
    }

    HoleSystem * holeSystem = initializeHoleSystem();
    HoleSystem * secondHoleSystem = initializeHoleSystem();
    HoleSystem * thirdHoleSystem = initializeHoleSystem();
    HoleSystem * fourthHoleSystem = initializeHoleSystem();
    Process * tempProcess;

    //parses the datafile, stores the value to be put into the memory in one 2D array, and the amount of times it's applied into a second 2D Array
    while(fgets(line, sizeof(line), fp))
    {
        if(line[strlen(line) - 1] == '\n')
        {
            line[strlen(line) - 1] = '\0';
        }
        word = strtok(line, " ");

        while(word != NULL)
        {
            if (parseCount != 0)
            {
                // printf("nono\n");
                parseCount--;
                memoryAmount[count] = strtol(word, &p, 10);
                tempProcess = initializeProcess(memoryValue[count], memoryAmount[count]);
                printf("line %d: char: %s, num: %d\n", count, memoryValue[count], memoryAmount[count]);
                insertBack(&holeSystem->processes, tempProcess);
                insertBack(&holeSystem->waitingProcesses, tempProcess);
                insertBack(&secondHoleSystem->processes, tempProcess);
                insertBack(&secondHoleSystem->waitingProcesses, tempProcess);
                insertBack(&thirdHoleSystem->processes, tempProcess);
                insertBack(&thirdHoleSystem->waitingProcesses, tempProcess);
                insertBack(&fourthHoleSystem->processes, tempProcess);
                insertBack(&fourthHoleSystem->waitingProcesses, tempProcess);

            }
            else if(parseCount == 0)
            {
                parseCount++;
                count++;
                strcpy(memoryValue[count], word);
            }
            word = strtok(NULL, " ");
        }
        memset(line, '\0', strlen(line));
    }
    fclose(fp);
    // holeSystem->waitingProcesses = holeSystem->processes;

    // HoleSystem * secondHoleSystem = holeSystem;
    // HoleSystem * thirdHoleSystem = holeSystem;
    // HoleSystem * fourthHoleSystem = holeSystem;

    //beginning of First Fit , checks for asterisks, until enough asteriks are avaliable to put the value into the memory
    //function then forloops backwards until the value is copied over all the empty spaces, then proceeds to the next value that was parsed


    firstFit(holeSystem);
    bestFit(secondHoleSystem);
    worstFit(thirdHoleSystem);
    nextFit(fourthHoleSystem);

    return 0;
}

void firstFit(HoleSystem * holeSystem)
{
    printf("First-Fit\n");
    while(getLength(holeSystem->waitingProcesses) != 0)
    {
        int nextHoleSize = checkNextHoleSize(holeSystem);
        if(nextHoleSize == 0)
        {
            swapProcess(holeSystem);
        }
        else
        {
            Process * headProcess = (Process*)getFromFront(holeSystem->waitingProcesses);
            if(nextHoleSize >= headProcess->processSize + checkBeginningHoleNum(holeSystem))
            {
                insertProcess(holeSystem);
            }
            else
            {

                swapProcess(holeSystem);
            }
        }
    }
    printFinishedInfo(holeSystem);
}


void bestFit(HoleSystem * holeSystem)
{

    printf("Best-Fit\n");
    while(getLength(holeSystem->waitingProcesses) != 0)
    {
        int nextHoleSize = checkNextHoleSize(holeSystem);
        if(nextHoleSize == 0)
        {
            swapProcess(holeSystem);
        }
        else
        {
            Process * headProcess = (Process*)getFromFront(holeSystem->waitingProcesses);
            if(nextHoleSize >= headProcess->processSize + checkBeginningHoleNum(holeSystem))
            {
                insertProcess(holeSystem);
            }
            else
            {

                swapProcess(holeSystem);
            }
        }
    }
    printFinishedInfo(holeSystem);

}

void worstFit(HoleSystem * holeSystem)
{
    printf("Worst-Fit\n");
    while(getLength(holeSystem->waitingProcesses) != 0)
    {
        int nextHoleSize = checkNextHoleSize(holeSystem);
        if(nextHoleSize == 0)
        {
            swapProcess(holeSystem);
        }
        else
        {
            Process * headProcess = (Process*)getFromFront(holeSystem->waitingProcesses);
            if(nextHoleSize >= headProcess->processSize + checkBeginningHoleNum(holeSystem))
            {
                insertProcess(holeSystem);
            }
            else
            {

                swapProcess(holeSystem);
            }
        }
    }
    printFinishedInfo(holeSystem);
}

void nextFit(HoleSystem * holeSystem)
{
    printf("Next-Fit\n");
    while(getLength(holeSystem->waitingProcesses) != 0)
    {
        int nextHoleSize = checkNextHoleSize(holeSystem);
        if(nextHoleSize == 0)
        {
            swapProcess(holeSystem);
        }
        else
        {
            Process * headProcess = (Process*)getFromFront(holeSystem->waitingProcesses);
            if(nextHoleSize >= headProcess->processSize + checkBeginningHoleNum(holeSystem))
            {
                insertProcess(holeSystem);
            }
            else
            {

                swapProcess(holeSystem);
            }
        }
    }
    printFinishedInfo(holeSystem);
}


void swapProcess(HoleSystem * holeSystem)
{
    Process * currentProcess = (Process*)getFromBack(holeSystem->runningProcesses);
    Process * replacementProcess = (Process*)getFromFront(holeSystem->waitingProcesses);
    if(currentProcess->processSize + checkNextHoleSize(holeSystem) >= replacementProcess->processSize)
    {
        if(currentProcess->swapCount < 3)
        {
            currentProcess->swapCount++;
            for(int i = 0; i < 128; i++)
            {
                if(holeSystem->memory[i] == currentProcess->processID[0])
                {
                    holeSystem->memory[i] = '*';
                }
            }

            int initHoleNum = checkBeginningHoleNum(holeSystem);
            for(int i = checkBeginningHoleNum(holeSystem); i < (initHoleNum + replacementProcess->processSize); i++)
            {
                holeSystem->memory[i] = replacementProcess->processID[0];
            }
            insertBack(&holeSystem->waitingProcesses, getFromFront(holeSystem->runningProcesses));
            deleteDataFromList(&holeSystem->runningProcesses, getFromFront(holeSystem->runningProcesses));
            insertBack(&holeSystem->runningProcesses, getFromFront(holeSystem->waitingProcesses));
            deleteDataFromList(&holeSystem->waitingProcesses, getFromFront(holeSystem->waitingProcesses));



        }
        else
        {
            for(int i = 0; i < 128; i++)
            {   if(holeSystem->memory[i] == currentProcess->processID[0])
                {
                    holeSystem->memory[i] = '*';
                }
            }
            int initHoleNum = checkBeginningHoleNum(holeSystem);
            for(int i = checkBeginningHoleNum(holeSystem); i < (initHoleNum + replacementProcess->processSize); i++)
            {
                holeSystem->memory[i] = replacementProcess->processID[0];
            }
            insertBack(&holeSystem->completedProcesses, getFromFront(holeSystem->runningProcesses));
            deleteDataFromList(&holeSystem->runningProcesses, getFromFront(holeSystem->runningProcesses));
            insertBack(&holeSystem->runningProcesses, getFromFront(holeSystem->waitingProcesses));
            deleteDataFromList(&holeSystem->waitingProcesses, getFromFront(holeSystem->waitingProcesses));

        }
        printProcessInfo(holeSystem, getFromBack(holeSystem->runningProcesses));
    }
    else
    {
        if(currentProcess->swapCount < 3)
        {
            currentProcess->swapCount++;
            for(int i = 0; i < 128; i++)
            {
                if(holeSystem->memory[i] == currentProcess->processID[0])
                {
                    holeSystem->memory[i] = '*';
                }
            }

            insertBack(&holeSystem->waitingProcesses, getFromFront(holeSystem->runningProcesses));
            deleteDataFromList(&holeSystem->runningProcesses, getFromFront(holeSystem->runningProcesses));
        }
        else
        {
            for(int i = 0; i < 128; i++)
            {   if(holeSystem->memory[i] == currentProcess->processID[0])
                {
                    holeSystem->memory[i] = '*';
                }
            }
            insertBack(&holeSystem->completedProcesses, getFromFront(holeSystem->runningProcesses));
            deleteDataFromList(&holeSystem->runningProcesses, getFromFront(holeSystem->runningProcesses));
        }
    }
}

void insertProcess(HoleSystem * holeSystem)
{
    Process * newProcess = getFromFront(holeSystem->waitingProcesses);
    int beginningNum = checkBeginningHoleNum(holeSystem);
    for(int i = beginningNum; i < (beginningNum + newProcess->processSize); i++)
    {
        holeSystem->memory[i] = newProcess->processID[0];
    }
    insertBack(&holeSystem->runningProcesses, newProcess);
    deleteDataFromList(&holeSystem->waitingProcesses, getFromFront(holeSystem->waitingProcesses));
    printProcessInfo(holeSystem, newProcess);

}


int checkBeginningHoleNum(HoleSystem * holeSystem)
{
    for(int i = 0; i < 128; i++)
    {
        if(holeSystem->memory[i] == '*')
        {
            return i;
        }
    }

    return -1;
}
int checkNextHoleSize(HoleSystem * holeSystem)
{
    int holeCount = 0;
    for(int i = 0; i < 128; i++)
    {
        if(holeSystem->memory[i] == '*')
        {
            while(holeSystem->memory[i] == '*')
            {
                holeCount++;
                i++;
            }

        }
    }

    return holeCount;
}

int checkHoleCount(HoleSystem * holeSystem)
{
    int holeCount = 0;
    for(int i = 0; i < 128; i++)
    {
        if(holeSystem->memory[i] == '*')
        {
            holeCount++;
            while(holeSystem->memory[i] == '*')
            {
                i++;
            }
        }
    }

    return holeCount;
}

int checkMemUsage(HoleSystem * holeSystem)
{
    int memUsage = 0;
    for(int i = 0; i < 128; i++)
    {
        if(holeSystem->memory[i] != '*')
        {
            memUsage++;
        }
    }

    return memUsage;
}

void printProcessInfo(HoleSystem * holeSystem, Process * process)
{
    if(process != NULL)
    {
        int memUsage = checkMemUsage(holeSystem);
        float newMemUsage = ((float)memUsage / 128) * 100 ;
        float newCumMemAverage = ((newMemUsage + holeSystem->cumulativeMemUsage)/2);
        holeSystem->cumulativeMemUsage = newCumMemAverage;
        holeSystem->totalLoadCount += process->processSize;
        holeSystem->averageHoleCount = (holeSystem->averageHoleCount + (float)checkHoleCount(holeSystem)) / 2;
        holeSystem->averageProcessCount = (holeSystem->averageProcessCount + process->processSize) / 2;
        printf("pid loaded, #processes = %d, #holes = %d, %%memusage = %.01f, cumulative %%mem = %.01f\n", process->processSize, checkHoleCount(holeSystem), newMemUsage, holeSystem->cumulativeMemUsage);
    }
}

void printFinishedInfo(HoleSystem * holeSystem)
{
    printf("Total loads = %d, average #processes = %.01f, average #holes = %.01f, cumulative %%mem = %.01f\n", holeSystem->totalLoadCount, holeSystem->averageProcessCount, holeSystem->averageHoleCount, holeSystem->cumulativeMemUsage);
}

Process * initializeProcess(char* processID, int processSize)
{
    Process * tempProcess = malloc(sizeof(Process));
    tempProcess->processID = malloc(sizeof(processID));
    strcpy(tempProcess->processID, processID);
    tempProcess->processSize = processSize;
    tempProcess->swapCount = 0;

    return tempProcess;
}

HoleSystem * initializeHoleSystem()
{
    HoleSystem* tempSystem = malloc(sizeof(HoleSystem));

    for(int i = 0; i < 128; i++)
    {
        strcpy(&tempSystem->memory[i], "*");
    }

    tempSystem->processes = initializeList(printGivenData, &free, compareData);
    tempSystem->cumulativeMemUsage = 0;
    tempSystem->averageHoleCount = 0;
    tempSystem->averageProcessCount = 0;
    tempSystem->totalLoadCount = 0;
    tempSystem->waitingProcesses = initializeList(printGivenData, &free, compareData);
    tempSystem->runningProcesses = initializeList(printGivenData, &free, compareData);
    tempSystem->completedProcesses = initializeList(printGivenData, &free, compareData);

    return tempSystem;
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

