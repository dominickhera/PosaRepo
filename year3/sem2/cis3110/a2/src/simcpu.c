#include "LinkedListAPI.h"
#include "creationFunctions.h"
#include "simcpu.h"

int main(int argc, char **argv)
{
    // Process * process = malloc(sizeof(int)* 5000);

    //decalre variables
    char line[256]; 
    char fileStorage[500][500];
    char * parse; 
    char *p; 
    int detailFlag = 0;
    int verboseFlag = 0;
    int roundRobinFlag = 0;
    int quantumInteger = 0;
    int threadSwitch = 0;
    int processSwitch = 0;
    int processCount = 0;
    int threadCount = 0;
    int burstCount = 0;
    int count = 0;

    // if(argc <= 1)
    // {
    //     printf("%d not enough args\n", argc);
    //     return 1;
    // }
    
    //checks for various flags and initiates them even though they dont completely work.
    for(int i = 0; i < argc; i++)
    {
        // printf("2\n");
        if(strcmp(argv[i],"-d") == 0)
        {
            printf("detail mode enabled\n");
            detailFlag = 1;
        }

        if(strcmp(argv[i], "-v") == 0)
        {
            printf("verbose mode enabled\n"); 
            verboseFlag = 1;
        }

        if(strcmp(argv[i], "-r") == 0)
        {
            
            roundRobinFlag = 1;
            quantumInteger = strtol(argv[i+1], &p, 10);
            printf("round robin mode enabled with quantumInteger: %d\n", quantumInteger);
        }
    }

    simSystem * simSystem = initializeSimSystem(threadSwitch, processSwitch);

    //takes the textfile and copys it all over into a 2D array
    while(fgets(line, sizeof(line), stdin) != NULL)
    {
        // int lineNumCount = 0;
        // for(int i = 0; line[i] != '\n'; i++)
        // {
            // if(line[i] == ' ')
            // {
                // lineNumCount++;
            // }
        // }
        // printf("%s which has %d numbers\n", line, lineNumCount + 1);

        strcpy(fileStorage[count], line);
        count++;
    }

    for(int i = 0; i < count; i++)
    {
        if(i == 0)
        {   
            int initCount = 0;
            parse = strtok(fileStorage[i], " ");
            while(parse != NULL)
            {
                switch(initCount)
                {
                    case 0:
                        processCount = strtol(parse, &p, 10);
                        // printf("Process Count: %d\n", process->processCount);
                        break;
                    case 1:
                        simSystem->threadSwitch = strtol(parse, &p, 10);
                        // printf("Thread Switch: %d\n", process->threadSwitch);
                        break;
                    case 2:
                        simSystem->processSwitch = strtol(parse, &p, 10);
                        // printf("Process Switch: %d\n", process->processSwitch);
                        break;
                    default:
                        // printf("default case\n");
                        break;
                }
                parse = strtok(NULL, " \n");
                initCount++; 
            }
        }
        i++;
        for(int k = 1; k < processCount+1; k++)
        {

            int initCount = 0;
            parse = strtok(fileStorage[i], " ");
            while(parse != NULL)
            {
                switch(initCount)
                {
                    case 0:
                    //     threadCount = strtol(parse, &p, 10);
                        printf("1Process Count: \n");
                        break;
                    case 1:
                        threadCount = strtol(parse, &p, 10);
                        // printf("Thread Switch: %d\n", process->threadSwitch);
                        break;
                    default:
                        // printf("default case\n");
                        break;
                }
                parse = strtok(NULL, " \n");
                initCount++; 
            }
            process * tempProcess = initializeProcess();

            i++;
            for(int m = 1; m < threadCount+1; m++)
            {
                i++;
                int initCount = 0;
                int tempArrivalTime = 0;
                parse = strtok(fileStorage[i], " ");
                while(parse != NULL)
                {
                    switch(initCount)
                    {
                        case 0:
                        //     processCount = strtol(parse, &p, 10);
                            printf("2Process Count\n");
                            break;
                        case 1:
                            tempArrivalTime = strtol(parse, &p, 10);
                            // printf("Thread Switch: %d\n", process->threadSwitch);
                            break;
                        case 2:
                            burstCount = strtol(parse, &p, 10);
                            // printf("Process Switch: %d\n", process->processSwitch);
                            break;
                        default:
                            // printf("default case\n");
                            break;
                    }
                    parse = strtok(NULL, " \n");
                    initCount++; 
                }
                thread * tempThread = initializeThread(tempArrivalTime);
                for(int j = 1; j < burstCount + 1; j++)
                {
                    i++;
                    if(j >= burstCount)
                    {
                        int tempCPUTime = 0;
                        int initCount = 0;
                        parse = strtok(fileStorage[i], " ");
                        while(parse != NULL)
                        {
                            switch(initCount)
                            {
                                case 0:
                                    processCount = strtol(parse, &p, 10);
                                    // printf("Process Count: %d\n", process->processCount);
                                    break;
                                case 1:
                                    tempCPUTime = strtol(parse, &p, 10);
                                    // printf("Thread Switch: %d\n", process->threadSwitch);
                                    break;
                                case 2:
                                //     simSystem->processSwitch = strtol(parse, &p, 10);
                                    printf("3Process Switch\n");
                                    break;
                                default:
                                    // printf("default case\n");
                                    break;
                            }
                            parse = strtok(NULL, " \n");
                            initCount++; 
                        }
                        // burst * tempBurst = initializeBurst(tempCPUTime, 0);
                        // insertBack(&tempThread->bursts, tempBurst);
                    }
                    else
                    {
                        i++;
                        int tempCPUTime = 0;
                        int tempIOTime = 0;
                        int initCount = 0;
                        parse = strtok(fileStorage[i], " ");
                        while(parse != NULL)
                        {
                            switch(initCount)
                            {
                                case 0:
                                //     processCount = strtol(parse, &p, 10);
                                    printf("4Process Count\n");
                                    break;
                                case 1:
                                    tempCPUTime = strtol(parse, &p, 10);
                                    // printf("Thread Switch: %d\n", process->threadSwitch);
                                    break;
                                case 2:
                                    tempIOTime = strtol(parse, &p, 10);
                                    // printf("Process Switch: %d\n", process->processSwitch);
                                    break;
                                default:
                                    // printf("default case\n");
                                    break;
                            }
                            parse = strtok(NULL, " \n");
                            initCount++; 
                        }

                        // burst * tempBurst = initializeBurst(tempCPUTime, tempIOTime);
                        // insertBack(&tempThread->bursts, tempBurst);
                    }
                }
                insertBack(&tempProcess->threads, tempThread);
            }
            insertBack(&simSystem->processes, tempProcess);
        }
        printf("line[%d]: %s", i, fileStorage[i]);
    }


    return 0;
}




