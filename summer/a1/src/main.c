#include "north.h"
#include "east.h"
#include "south.h"
#include "west.h"
// #include "functions.h"
#include <stdio.h>
#include <string.h>

void printFunction(void * data)
{
	printf("%s", (char *)data);
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
    char * tempChar = malloc(sizeof(char)*10);
    char * tempNum = malloc(sizeof(char)*10);
    char * parse;
    int maxWaitTime = 0;
    int averageWaitTime = 0;
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
            	printf("N");
                parse = strtok (NULL, " ");
                tempChar = parse;
                initializeNorthNode((void *) tempChar);
                parse = strtok (NULL, " ");
                tempNum = parse;
                insertNorthFront(northList, (void *) tempChar, (void *) tempNum);
                printNorthData(northList);
                printNorthTimeData(northList);
            }
            else if(strcmp(parse, "E") == 0)
            {
                printf("E");
                parse = strtok (NULL, " ");
                tempChar = parse;
                initializeEastNode((void *) tempChar);
                parse = strtok (NULL, " ");
                tempNum = parse;
                insertEastFront(eastList, (void *) tempChar, (void *) tempNum);
                printEastData(eastList);
                printEastTimeData(eastList);
            }
            else if(strcmp(parse, "S") == 0)
            {
                printf("S");
                parse = strtok (NULL, " ");
                tempChar = parse;
                initializeSouthNode((void *) tempChar);
                parse = strtok (NULL, " ");
                tempNum = parse;
                insertSouthFront(southList, (void *) tempChar, (void *)tempNum);
                printSouthData(southList);
                printSouthTimeData(southList);
            }
            else if(strcmp(parse, "W") == 0)
            {
                printf("W");
                parse = strtok (NULL, " ");
                tempChar = parse;
                initializeWestNode((void *) tempChar);
                parse = strtok (NULL, " ");
                tempNum = parse;
                insertWestFront(westList, (void *) tempChar, (void *)tempNum);
                printWestData(westList);
                printWestTimeData(westList);
            }
            parse = strtok (NULL, " ");
        }
    }  

    printf("\n");

    printf("Max Wait Time: %d\n", maxWaitTime); 
    printf("Average Wait Time: %d\n", averageWaitTime); 

    return 0;
}
