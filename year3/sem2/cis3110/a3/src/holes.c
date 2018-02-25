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
    char memory[127][127];
    char memoryValue[127][127];
    int memoryAmount[127];
    char * word;
    int count = 0;
    // int processCount = 0;
    int cycleCount = 1;
    int emptyCount = 0;
    int parseCount = 0;

    fp = fopen(argv[1], "r");

    if(fp == NULL)
    {
        printf("couldn't find file\nexiting...\n");
        exit(1);
    }

    //copys an astrerisk for each empty spot in the memory
    for(int i = 0; i < 128; i++)
    {

        strcpy(memory[i], "*");

    }

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
                printf("line %d: char: %s, num: %d\n", count, memoryValue[count], memoryAmount[count]);

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


    //beginning of First Fit , checks for asterisks, until enough asteriks are avaliable to put the value into the memory
    //function then forloops backwards until the value is copied over all the empty spaces, then proceeds to the next value that was parsed
    printf("\n\nFirst-Fit\n");

    for(int k = 0; k < count; k++)
    {
        for(int i = 0; i < 128; i++)
        {
            if(strcmp(memory[i], "*") == 0)
            {
                emptyCount++;
                if(emptyCount >= memoryAmount[cycleCount])
                {
                    // printf("\nemptycount: %d, memoryAmount: %d, i: %d\n", emptyCount, memoryAmount[cycleCount], (i + 1));
                    for(int j = i; j > (i - emptyCount); j--)
                    {
                        // printf("%d val\n", (j + 1));
                        strcpy(memory[j], memoryValue[cycleCount]);
                    }
                    cycleCount++;
                    emptyCount = 0;
                    break;
                }
                // printf("line %d: %s\n", i, memory[i]);
            }
            // else
            // {
            	// printf(".");
            // 	printf("line %d: %s\n", i, memory[i]);
            // }

        }
    }


    //prints all the memory values, mainly for debugging reasons
    for(int i = 0; i < 128; i++)
    {
        printf("line %d: %s\n", i + 1, memory[i]);
    }


    return 0;
}
