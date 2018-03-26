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
    // char memory[127][127];
    char memoryValue[127][127];
    int memoryAmount[127];
    char * word;
    int count = 0;
    // int processCount = 0;
    // int cycleCount = 1;
    // int emptyCount = 0;
    int parseCount = 0;

    fp = fopen(argv[1], "r");

    if(fp == NULL)
    {
        printf("couldn't find file\nexiting...\n");
        exit(1);
    }

    HoleSystem * holeSystem = initializeHoleSystem();
    Process * tempProcess;
    //copys an astrerisk for each empty spot in the memory
    // for(int i = 0; i < 128; i++)
    // {

        // strcpy(memory[i], "*");

    // }
// printf("hello\n");
    printf("\n\n");


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
            }
            else if(parseCount == 0)
            {
                parseCount++;
                count++;
                // printf("fuck\n");
                strcpy(memoryValue[count], word);
            }
            // printf("mum\n");
            word = strtok(NULL, " ");
        }
        // printf("ok\n");
        memset(line, '\0', strlen(line));
    }
    // printf("why\n");
    fclose(fp);
    // holeSystem->waitingProcesses = holeSystem->processes;

    // HoleSystem * secondHoleSystem = holeSystem;
    // HoleSystem * thirdHoleSystem = holeSystem;
    // HoleSystem * fourthHoleSystem = holeSystem;

    //beginning of First Fit , checks for asterisks, until enough asteriks are avaliable to put the value into the memory
    //function then forloops backwards until the value is copied over all the empty spaces, then proceeds to the next value that was parsed
  

    firstFit(holeSystem);

    // printf("\n\nFirst-Fit\n");

    // for(int k = 0; k < count; k++)
    // {
    //     for(int i = 0; i < 128; i++)
    //     {
    //         if(strcmp(memory[i], "*") == 0)
    //         {
    //             emptyCount++;
    //             if(emptyCount >= memoryAmount[cycleCount])
    //             {
    //                 // printf("\nemptycount: %d, memoryAmount: %d, i: %d\n", emptyCount, memoryAmount[cycleCount], (i + 1));
    //                 for(int j = i; j > (i - emptyCount); j--)
    //                 {
    //                     // printf("%d val\n", (j + 1));
    //                     strcpy(memory[j], memoryValue[cycleCount]);
    //                 }
    //                 cycleCount++;
    //                 emptyCount = 0;
    //                 break;
    //             }
    //             // printf("line %d: %s\n", i, memory[i]);
    //         }
    //         // else
    //         // {
    //         	// printf(".");
    //         // 	printf("line %d: %s\n", i, memory[i]);
    //         // }

    //     }
    // }


    // //prints all the memory values, mainly for debugging reasons
    // for(int i = 0; i < 128; i++)
    // {
    //     printf("line %d: %s\n", i + 1, memory[i]);
    // }


    return 0;
}

void firstFit(HoleSystem * holeSystem)
{
    printf("First-Fit\n");
    while(getLength(holeSystem->waitingProcesses) != 0)
    {
        // printf("hello\n");
        printf("memory: %s\n", holeSystem->memory);
        int nextHoleSize = checkNextHoleSize(holeSystem);
        printf("next hole size is %d\n", nextHoleSize);
        if(nextHoleSize == 0)
        {
            swapProcess(holeSystem);
        }
        else
        {
            // void* elem;
            // ListIterator elemIter = createIterator(holeSystem->waitingProcesses);
            // elem = nextElement(&elemIter);
            Process * headProcess = (Process*)getFromFront(holeSystem->waitingProcesses);
            printf("front of head process is the size %d\n", headProcess->processSize);
            if(nextHoleSize >= headProcess->processSize)
            {
                insertProcess(holeSystem);
            }
            else
            {
                swapProcess(holeSystem);
            }
        }
    }
    printf("memory: %s\n", holeSystem->memory);
    printFinishedInfo(holeSystem);

}

void swapProcess(HoleSystem * holeSystem)
{
    void* elem;
    // void* otherElem;
    // ListIterator otherElemIter = createIterator(holeSystem->waitingProcesses);
    // otherElem = nextElement(&otherElemIter);
    Process * replacementProcess = (Process*)getFromFront(holeSystem->waitingProcesses);
    ListIterator elemIter = createIterator(holeSystem->runningProcesses);
    while((elem = nextElement(&elemIter)) != NULL)
    {

        Process * currentProcess = (Process*)elem;
        if(currentProcess->processSize >= replacementProcess->processSize)
        {
            if(currentProcess->swapCount < 3)
            {
                currentProcess->swapCount++;
                for(int i = 0; i < 128; i++)
                {
                    if(strcmp(&holeSystem->memory[i], currentProcess->processID)== 0)
                    {
                        holeSystem->memory[i] = '*';
                    }
                }

                for(int i = checkBeginningHoleNum(holeSystem); i < (checkBeginningHoleNum(holeSystem) + replacementProcess->processSize); i++)
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
                {
                    if(strcmp(&holeSystem->memory[i], currentProcess->processID)== 0)
                    {
                        holeSystem->memory[i] = '*';
                    }
                }

                for(int i = checkBeginningHoleNum(holeSystem); i < (checkBeginningHoleNum(holeSystem) + replacementProcess->processSize); i++)
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
    }
}

void insertProcess(HoleSystem * holeSystem)
{
    Process * newProcess = getFromFront(holeSystem->waitingProcesses);
    int beginningNum = checkBeginningHoleNum(holeSystem);
    // printf("beginnging num is %d, processsize is %d, char was %c\n", beginningNum, newProcess->processSize, newProcess->processID[0]);
    // char processIDChar = &newProcess->processID[0];
    for(int i = beginningNum; i < (beginningNum + newProcess->processSize); i++)
    {
        holeSystem->memory[i] = newProcess->processID[0];
        // strcpy(&holeSystem->memory[i], &newProcess->processID[0]);
        // printf("memory while inserting%c\n", holeSystem->memory[i]);
    }
    // printf("memory full is %s\n", holeSystem->memory);
    insertBack(&holeSystem->runningProcesses, newProcess);
    deleteDataFromList(&holeSystem->waitingProcesses, getFromFront(holeSystem->waitingProcesses));
    printProcessInfo(holeSystem, newProcess);
    // void* elem;
    // ListIterator elemIter = createIterator(holeSystem->runningProcesses);
    // while((elem = nextElement(&elemIter)) != NULL)
    // {

    // }

}


int checkBeginningHoleNum(HoleSystem * holeSystem)
{
    for(int i = 0; i < 128; i++)
    {
        if(holeSystem->memory[i] == '*')
        {
            // printf("i is %d\n", i);
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
    printf("memusage is %d\n", memUsage);

    return memUsage;
}

void printProcessInfo(HoleSystem * holeSystem, Process * Process)
{
    // int memUsage = checkMemUsage(holeSystem);
    // double newMemUsage = memUsage / 128 ;
    // printf("pls work %f\n", newMemUsage);
    // printf("test\n");
    printf("pid loaded, #processes = %d, #holes = %d, %%memusage = %d, cumulative %%mem = %.01d\n", Process->processSize, checkHoleCount(holeSystem), checkMemUsage(holeSystem), holeSystem->cumulativeMemUsage);

}

void printFinishedInfo(HoleSystem * holeSystem)
{
    printf("test\n");
    // printf("Total loads = %d, average #processes = %.01f, average #holes = %.01f, cumulative %%mem = %d\n");
}

Process * initializeProcess(char* processID, int processSize)
{
    // printf("process id is %s, size is %d\n", processID, processSize);
    Process * tempProcess = malloc(sizeof(Process));
    tempProcess->processID = malloc(sizeof(processID));
    strcpy(tempProcess->processID, processID);
    tempProcess->processSize = processSize;
    tempProcess->swapCount = 0;


    // printf("process id is %s, size is %d\n", processID, processSize);
    return tempProcess;
}

HoleSystem * initializeHoleSystem()
{
    HoleSystem* tempSystem = malloc(sizeof(HoleSystem));

    for(int i = 0; i < 128; i++)
    {
        // printf("i is %d\n", i);
        strcpy(&tempSystem->memory[i], "*");

    }

    tempSystem->processes = initializeList(printGivenData, &free, compareData);
    tempSystem->cumulativeMemUsage = 0;
    tempSystem->averageHoleCount = 0;
    tempSystem->averageProcessCount = 0;
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







