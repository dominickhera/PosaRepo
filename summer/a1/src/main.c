// #include "north.h"
// #include "east.h"
// #include "south.h"
//
// #include "parse.h"
#include <stdio.h>
#include <string.h>

// void printFunction(void * data)
// {
// 	printf("%s", (char *)data);
// }

// int compareFunction(const void *first,const void *second)
// {
// 	int tempVal = 0;

// 	if(*(int *)first > *(int *)second || *(int *)first == *(int *)second)
// 	{
// 		return first;
// 	}
// 	else
// 	{
// 		tempVal = first;
// 		first = second;
// 		second = tempVal;
// 		return first;
// 	}
// }

int main(int argc, char ** argv)
{
    char line[256];
    char * parse;
    int clk = 1;
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

    while(fgets(line, sizeof(line), fp) != NULL)
    {
        parse = strtok (line," ");
        while (parse != NULL)
        {
            printf ("%s\n",parse);
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

    return 0;
}
