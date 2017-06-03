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
		return first;
	}
	else
	{
		tempVal = first;
		first = second;
		second = tempVal;
		return first;
	}
}

int main(int argc, char ** argv)
{
    char line[256];
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

 //    Array * arr = createArray(3, &printme, &free); //because my data is just a string I can send free as the cleanup function
	// char * name = malloc(sizeof(char)*10);
	// char * cat = malloc(sizeof(char)*10);
	// char * dog = malloc(sizeof(char)*10);
	// strcpy(name, "judi");
	// strcpy(cat, "baldr");
	// strcpy(dog, "branwen");

	NorthList * northData = initializeNorthList(&printFunction, &free, &compareFunction);
	EastList * eastData = initializeEastList(&printFunction, &free, &compareFunction);
	SouthList * southData = initializeSouthList(&printFunction, &free, &compareFunction);
	WestList * westData = initializeWestList(&printFunction, &free, &compareFunction);

    while(fgets(line, sizeof(line), fp) != NULL)
    {
        parse = strtok (line," ");
        printf("butts");
        while (parse != NULL)
        {
            printf ("%s",parse);
            if(strcmp(parse, "N") == 0)
            {
            	// printf(" that car is coming north ");
            }
            // printf(" butts ");
            parse = strtok (NULL, " ");
        }
        // printf("%s", line); 
    }  

    // pch = strtok (str," ");
    // while (pch != NULL)
    //  {
    //    printf ("%s\n",pch);
    //    pch = strtok (NULL, " ");
    //  }

    printf("\n");

    printf("Max Wait Time: %d\n", maxWaitTime); 
    printf("Average Wait Time: %d\n", averageWaitTime); 

    return 0;
}
