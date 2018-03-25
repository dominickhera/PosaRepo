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
    //copys an astrerisk for each empty spot in the memory
    // for(int i = 0; i < 128; i++)
    // {

        // strcpy(memory[i], "*");

    // }

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
                parseCount--;
                memoryAmount[count] = strtol(word, &p, 10);
                Process * tempProcess = initializeProcess(memoryValue[count], memoryAmount[count]);
                printf("line %d: char: %s, num: %d\n", count, memoryValue[count], memoryAmount[count]);
                insertBack(&holeSystem->processes, tempProcess);
                insertBack(&holeSystem->waitingProcesses, tempProcess);
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

        int nextHoleSize = checkNextHoleSize(holeSystem);
        if(nextHoleSize == 0)
        {
            swapProcess(holeSystem);
        }
        else
        {
            void* elem;
            ListIterator elemIter = createIterator(holeSystem->waitingProcesses);
            elem = nextElement(&elemIter);
            Process * headProcess = (Process*)elem;
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
        if((currentProcess->processSize + checkNextHoleSize(holeSystem)) >= replacementProcess->processSize)
        {
            if(currentProcess->swapCount < 3)
            {
                currentProcess->swapCount++;
                for(int i = 0; i < 128; i++)
                {
                    if(holeSystem->memory[i] == currentProcess->processID)
                    {
                        strcpy(&holeSystem->memory[i], "*");
                    }
                }

                for(int i = checkBeginningHoleNum(holeSystem); i < (128 - replacementProcess->processSize); i++)
                {
                    strcpy(&holeSystem->memory[i], replacementProcess->processID);
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
                    if(holeSystem->memory[i] == currentProcess->processID)
                    {
                        strcpy(&holeSystem->memory[i], "*");
                    }
                }

                for(int i = checkBeginningHoleNum(holeSystem); i < (128 - replacementProcess->processSize); i++)
                {
                    strcpy(&holeSystem->memory[i], replacementProcess->processID);
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
    for(int i = beginningNum; i < (128 - newProcess->processSize); i++)
    {
        strcpy(&holeSystem->memory[i], newProcess->processID);
    }
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
        if(holeSystem->memory[i] != '*')
        {
            while(holeSystem->memory[i] != '*')
            {
                holeCount++;
            }
            return holeCount;
        }
    }

    return 0;
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

int checkMemUsage(HoleSystem * HoleSystem)
{
    int memUsage = 0;
    for(int i = 0; i < 128; i++)
    {
        if(HoleSystem->memory[i] != '*')
        {
            memUsage++;
        }
    }

    return memUsage/128;
}

void printProcessInfo(HoleSystem * holeSystem, Process * Process)
{

    printf("test\n");
    // printf("pid loaded, #processes = %d, #holes = %d, %%memusage = %d, cumulative %%mem = %d\n", Process->processSize, checkHoles(HoleSystem), checkMemUsage(HoleSystem));

}

void printFinishedInfo(HoleSystem * holeSystem)
{
    printf("test\n");
    // printf("Total loads = %d, average #processes = %.01f, average #holes = %.01f, cumulative %%mem = %d\n");
}

Process * initializeProcess(char* processID, int processSize)
{
    Process* tempProcess = malloc(sizeof(Process));
    // tempProcess->processID = malloc(sizeof(processID));
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







