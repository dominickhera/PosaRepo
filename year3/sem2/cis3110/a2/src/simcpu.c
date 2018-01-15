#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simcpu.h"

int main(int argc, char **argv)
{
    Process * process = malloc(sizeof(int)* 5000);

    //decalre variables
    char line[256]; 
    char fileStorage[500][500];
    char * parse; 
    char *p; 
    process->detailFlag = 0;
    process->verboseFlag = 0;
    process->roundRobinFlag = 0;
    int count = 0;   
    int initCount = 0; 
    int processNumBuffer = 0;
    int tempProcessNumBuffer = 0; 


//checks for various flags and initiates them even though they dont completely work.
    for(int i = 0; i < argc; i++)
    {
        // printf("2\n");
        if(strcmp(argv[i],"-d") == 0)
        {
            printf("detail mode enabled\n");
            process->detailFlag++;
        }

        if(strcmp(argv[i], "-v") == 0)
        {
            printf("verbose mode enabled\n"); 
            process->verboseFlag = 1;
        }

        if(strcmp(argv[i], "-r") == 0)
        {
            printf("round robin mode enabled\n");
            process->roundRobinFlag = 1;
            process->quantumInteger = strtol(argv[i+1], &p, 10); 
        }
    }  


//takes the textfile and copys it all over into a 2D array
    while(fgets(line, sizeof(line), stdin) != NULL)
    {
        strcpy(fileStorage[count], line);
        count++;
    }

//parses the 2D array and seperates each of the numbers
// presumable where i wouldve put all the numbers into the struct buttttttt
    for(int i = 0; i < count; i++)
    {
        initCount = 0;

        parse = strtok(fileStorage[i], " ");
        while(parse != NULL)
        {
            printf("%s ", parse);
            parse = strtok(NULL, " \n");
            initCount++;
        }
        printf("\n");
    }


//specifically parses the first line and stores various peieces into the process struct
    parse = strtok(fileStorage[0], " ");
    while(parse != NULL)
    {
        switch(initCount)
        {
            case 0:
                process->processCount = strtol(parse, &p, 10);
                // printf("Process Count: %d\n", process->processCount);
                break;
            case 1:
                process->threadSwitch = strtol(parse, &p, 10);
                // printf("Thread Switch: %d\n", process->threadSwitch);
                break;
            case 2:
                process->processSwitch = strtol(parse, &p, 10);
                // printf("Process Switch: %d\n", process->processSwitch);
                break;
            default:
                // printf("default case\n");
                break;
        }
        parse = strtok(NULL, " \n");
        initCount++; 
    }


//speicially parses second line to initiate storing all the other data in the process struct to use for other for loops
    initCount = 0;
    parse = strtok(fileStorage[1], " ");
    while(parse != NULL)
        // printf("no\n");
    {
        switch(initCount)
        {
            case 0:
                process->cpuThread = malloc(sizeof(process) * 500);
                processNumBuffer = strtol(parse, &p, 10);
                // process->cpuThread[0].processNum = strtol(parse, &p, 10);
                break;
            case 1:
                // process->cpuThread = malloc(sizeof(process) * (strtol(parse, &p, 10) * 3));
                process->cpuThread[0].threadNum = strtol(parse, &p, 10);
                // printf("Thread Count: %d\n", process->cpuThread[0].threadNum);
                break;
            default:
                break;
        }
        parse = strtok(NULL, " \n");
        initCount++; 
    }
    // for(int j = 2; i < count; j++)
    // {
    //     for(int i = 1; i < process->cpuThread[0].threadNum; i++)
    //     {

    //     }
    // }


//ideally, this is where the end data would've been presented
//but alas it all just ends up as 0 since the simulation is never done.
    if(process->roundRobinFlag != 1)
    {
        printf("\nFCFS: \n\n");
    }
    else
    {
        printf("\nRound Robin (quantum = %d time units):\n\n", process->quantumInteger);
    }

    printf("Total Time required is %d time units\nAverage Turnaround Time is %d time units\nCPU Utilization is %d%%\n\n", process->totalTime, process->averageTurnAroundTime, process->cpuUtilization);

    if(process->detailFlag == 1)
    {
        printf("details should be here but they aren't\n");
    }

    return 0;
}
