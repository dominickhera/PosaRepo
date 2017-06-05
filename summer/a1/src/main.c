#include "north.h"
#include "east.h"
#include "south.h"
#include "west.h"
// #include "functions.h"
#include <stdio.h>
#include <string.h>

void printFunction(void * data)
{
    printf("%s\n", (char *)data);
}

int compareFunction(const void *first,const void *second)
{
    int tempVal = 0;

    if(*(int *)first > *(int *)second || *(int *)first == *(int *)second)
    {
        return *(int *)first;
    }
    else
    {
        tempVal = *(int *)first;
        *(int *)first = *(int *)second;
        *(int *)second = tempVal;
        return *(int *)first;
    }
}

int main(int argc, char ** argv)
{
    char line[256];
    char northDStore[256][256];
    char northNStore[256][256];
    char eastDStore[256][256];
    char eastNStore[256][256];
    char southDStore[256][256];
    char southNStore[256][256];
    char westDStore[256][256];
    char westNStore[256][256];
    char * tempChar = malloc(sizeof(char)*10);
    char * tempNum = malloc(sizeof(char)*10);
    // char * westDirectionStore = malloc(sizeof(char) * 256); 
    // char * westNumStore = malloc(sizeof(char) * 256); 
    char * parse;
    int maxWaitTime = 0;
    int averageWaitTime = 0;
    int northCount = 0;
    int eastCount = 0;
    int southCount = 0;
    int westCount = 0;
    int swapCount = 0;
    int subCount = 0;
    // int clk = 1;
    FILE * fp;

    fp = fopen(argv[1], "r");

    if(fp == NULL)
    {
        printf("could not find file\n");
        return 0;
    }

    if(argc != 2)
    {
        printf("incorrect amount of input\n");
    }

    NorthList * northList = initializeNorthList(&printFunction, &free, &compareFunction);
    EastList * eastList = initializeEastList(&printFunction, &free, &compareFunction);
    SouthList * southList = initializeSouthList(&printFunction, &free, &compareFunction);
    WestList * westList = initializeWestList(&printFunction, &free, &compareFunction);


    while(fgets(line, sizeof(line), fp) != NULL)
    {
        parse = strtok (line," ");
        while (parse != NULL)
        {
            if(strcmp(parse, "N") == 0)
            {
                // printf("N");
                parse = strtok (NULL, " ");
                tempChar = parse;
                initializeNorthNode((void *) tempChar);
                parse = strtok (NULL, " ");
                tempNum = parse;
                strcpy(northDStore[northCount], tempChar);
                strcpy(northNStore[northCount], tempNum);
                northCount++;
            }
            else if(strcmp(parse, "E") == 0)
            {
                // printf("E");
                parse = strtok (NULL, " ");
                tempChar = parse;
                initializeEastNode((void *) tempChar);
                parse = strtok (NULL, " ");
                tempNum = parse;
                strcpy(eastDStore[eastCount], tempChar);
                strcpy(eastNStore[eastCount], tempNum);
                eastCount++;
            }
            else if(strcmp(parse, "S") == 0)
            {
                // printf("S");
                parse = strtok (NULL, " ");
                tempChar = parse;
                initializeSouthNode((void *) tempChar);
                parse = strtok (NULL, " ");
                tempNum = parse;
                strcpy(southDStore[southCount], tempChar);
                strcpy(southNStore[southCount], tempNum);
                southCount++;
            }
            else if(strcmp(parse, "W") == 0)
            {
                // printf("W");
                parse = strtok (NULL, " ");
                tempChar = parse;
                initializeWestNode((void *) tempChar);
                parse = strtok (NULL, " ");
                tempNum = parse;
                strcpy(westDStore[westCount], tempChar);
                strcpy(westNStore[westCount], tempNum);
                westCount++;
            }
            parse = strtok (NULL, " ");
        }
    }  

    while(subCount != northCount*2)
    {
        char * swapVal = malloc(sizeof(char) * 15);
        char * secondSwapVal = malloc(sizeof(char) * 15);

        if(atoi(northNStore[swapCount + 1]) > northCount || swapCount > northCount)
        {
            swapCount = 0;
        }
        else if(atoi(northNStore[swapCount]) > atoi(northNStore[swapCount+1]))
        {
            strcpy(swapVal, northNStore[swapCount]);
            strcpy(northNStore[swapCount], northNStore[swapCount + 1]);
            strcpy(northNStore[swapCount + 1], swapVal);

            strcpy(secondSwapVal, northDStore[swapCount]);
            strcpy(northDStore[swapCount], northDStore[swapCount + 1]);
            strcpy(northDStore[swapCount + 1], secondSwapVal);
        }
        swapCount++;
        subCount++;
    }

    for(int i = 0; i < northCount; i++)
    {
        // printf("W %s %s", westDStore[i], westNStore[i]);
        insertNorthFront(northList, (void *) northDStore[i], (void *)northNStore[i]);
    }

    subCount = 0;

    while(subCount != eastCount*2)
    {
        char * swapVal = malloc(sizeof(char) * 15);
        char * secondSwapVal = malloc(sizeof(char) * 15);

        if(atoi(eastNStore[swapCount + 1]) > eastCount || swapCount > eastCount)
        {
            swapCount = 0;
        }
        else if(atoi(eastNStore[swapCount]) > atoi(eastNStore[swapCount+1]))
        {
            strcpy(swapVal, eastNStore[swapCount]);
            strcpy(eastNStore[swapCount], eastNStore[swapCount + 1]);
            strcpy(eastNStore[swapCount + 1], swapVal);

            strcpy(secondSwapVal, westDStore[swapCount]);
            strcpy(eastDStore[swapCount], eastDStore[swapCount + 1]);
            strcpy(eastDStore[swapCount + 1], secondSwapVal);
        }
        swapCount++;
        subCount++;
    }

    for(int i = 0; i < eastCount; i++)
    {
        // printf("W %s %s", westDStore[i], westNStore[i]);
        insertEastFront(eastList, (void *) eastDStore[i], (void *)eastNStore[i]);
    }

    subCount = 0;

    while(subCount != southCount*2)
    {
        char * swapVal = malloc(sizeof(char) * 15);
        char * secondSwapVal = malloc(sizeof(char) * 15);

        if(atoi(southNStore[swapCount + 1]) > southCount || swapCount > southCount)
        {
            swapCount = 0;
        }
        else if(atoi(southNStore[swapCount]) > atoi(southNStore[swapCount+1]))
        {
            strcpy(swapVal, southNStore[swapCount]);
            strcpy(southNStore[swapCount], southNStore[swapCount + 1]);
            strcpy(southNStore[swapCount + 1], swapVal);

            strcpy(secondSwapVal, southDStore[swapCount]);
            strcpy(southDStore[swapCount], southDStore[swapCount + 1]);
            strcpy(southDStore[swapCount + 1], secondSwapVal);
        }
        swapCount++;
        subCount++;
    }

    for(int i = 0; i < southCount; i++)
    {
        // printf("W %s %s", westDStore[i], westNStore[i]);
        insertSouthFront(southList, (void *) southDStore[i], (void *)southNStore[i]);
    }


    subCount = 0;
    while(subCount != westCount*2)
    {
        char * swapVal = malloc(sizeof(char) * 15);
        char * secondSwapVal = malloc(sizeof(char) * 15);

        if(atoi(westNStore[swapCount + 1]) > westCount || swapCount > westCount)
        {
            swapCount = 0;
        }
        else if(atoi(westNStore[swapCount]) > atoi(westNStore[swapCount+1]))
        {
            strcpy(swapVal, westNStore[swapCount]);
            strcpy(westNStore[swapCount], westNStore[swapCount + 1]);
            strcpy(westNStore[swapCount + 1], swapVal);

            strcpy(secondSwapVal, westDStore[swapCount]);
            strcpy(westDStore[swapCount], westDStore[swapCount + 1]);
            strcpy(westDStore[swapCount + 1], secondSwapVal);
        }
        swapCount++;
        subCount++;
    }

    for(int i = 0; i < westCount; i++)
    {
        // printf("W %s %s", westDStore[i], westNStore[i]);
        insertWestFront(westList, (void *) westDStore[i], (void *)westNStore[i]);
    }

    subCount = 0;
    
    while(subCount != westCount*2)
    {
        char * swapVal = malloc(sizeof(char) * 15);
        char * secondSwapVal = malloc(sizeof(char) * 15);

        if(atoi(westNStore[swapCount + 1]) > westCount || swapCount > westCount)
        {
            swapCount = 0;
        }
        else if(atoi(westNStore[swapCount]) > atoi(westNStore[swapCount+1]))
        {
            strcpy(swapVal, westNStore[swapCount]);
            strcpy(westNStore[swapCount], westNStore[swapCount + 1]);
            strcpy(westNStore[swapCount + 1], swapVal);

            strcpy(secondSwapVal, westDStore[swapCount]);
            strcpy(westDStore[swapCount], westDStore[swapCount + 1]);
            strcpy(westDStore[swapCount + 1], secondSwapVal);
        }
        swapCount++;
        subCount++;
    }

    for(int i = 0; i < westCount; i++)
    {
        // printf("W %s %s", westDStore[i], westNStore[i]);
        insertWestFront(westList, (void *) westDStore[i], (void *)westNStore[i]);
    }
    // printWestForward(westList);

    printf("\n\nMax Wait Time: %d\n", maxWaitTime); 
    printf("Average Wait Time: %d\n", averageWaitTime); 

    return 0;
}
