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
    char tempChar;
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

	NorthList * northList = initializeNorthList(&printFunction, &free, &compareFunction);
	// EastList * eastList = initializeEastList(&printFunction, &free, &compareFunction);
	// SouthList * southList = initializeSouthList(&printFunction, &free, &compareFunction);
	// WestList * westList = initializeWestList(&printFunction, &free, &compareFunction);


    // NorthList * northList = NULL;

    while(fgets(line, sizeof(line), fp) != NULL)
    {
        parse = strtok (line," ");
        // printf("butts");
        while (parse != NULL)
        {
            // printf ("%s",parse);
            if(strcmp(parse, "N") == 0)
            {
            	// printf("north ");
                parse = strtok (NULL, " ");
                tempChar = *parse;
                insertNorthFront(northList, (void **) tempChar);
                printNorthForward(northList);
                // northData = &tempChar;
                // printf(" %c ", northData);
                parse = strtok (NULL, " ");
                tempChar = *parse;
                // printf(" %c\n", tempChar);
            }
            else if(strcmp(parse, "E") == 0)
            {
                // printf("east ");
                parse = strtok (NULL, " ");
                tempChar = *parse;
                // printf(" %c ", tempChar);
                parse = strtok (NULL, " ");
                tempChar = *parse;
                // printf(" %c\n", tempChar);
            }
            else if(strcmp(parse, "S") == 0)
            {
                // printf("south ");
                parse = strtok (NULL, " ");
                tempChar = *parse;
                // printf(" %c ", tempChar);
                parse = strtok (NULL, " ");
                tempChar = *parse;
                // printf(" %c\n", tempChar);
            }
            else if(strcmp(parse, "W") == 0)
            {
                // printf("west ");
                parse = strtok (NULL, " ");
                tempChar = *parse;
                // printf(" %c ", tempChar);
                parse = strtok (NULL, " ");
                tempChar = *parse;
                // printf(" %c\n", tempChar);
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
