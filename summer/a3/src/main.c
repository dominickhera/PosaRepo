#include "heap.h"
#include "functions.h"

int main(int argc, char* argv[])
{

    // int choice = 0;
    char * fileName = argv[1];
    char line[256];
    char tempID[256];
    char tempPriority[50];
    char tempSymptomCode[50];
    int parseCount = 0;
    FILE *fp;

    if(argc != 2)
    {
        printf("wrong amount of arguements entered\n");
        exit(1);
    }


    fp = fopen(fileName, "r");

    if(fp == NULL)
    {
        printf("invalid data file\n");
        exit(1);
    }



    Heap * heap = createHeap(500, MIN_HEAP, &free, &printData, &compareFunction);

    while(fgets(line, sizeof(line), fp) != NULL)
    {
        char * parse;

        if(line[strlen(line) - 1] == '\n')
        {
            line[strlen(line) - 1] = '\0';
        }

        parse = strtok(line, " ");
        // printf("%s\n", parse);
        strcpy(tempID, parse);

        while((parse = strtok(NULL, " ")) != NULL)
        {
            if(parseCount == 0)
            {
                strcpy(tempPriority, parse);
                // printf("p1: %s\n", tempPriority);
                parseCount++;
            }
            else
            {

                strcpy(tempSymptomCode, parse);
                parseCount--;
            }

        }

        // printf("ID: %s, Priority: %s, Symptom Code: %s\n", tempID, tempPriority, tempSymptomCode);
        // if(strcmp(parse, " ") == 0)
        // {
        // 	printf("butts\n");
        // }
        insertHeapNode(heap, atoi(tempPriority), tempID, tempSymptomCode);
        // printf("heapID: %d, ID: %s, Priority: ")
        memset(tempID, 0, strlen(line));
        memset(tempPriority, 0, strlen(line));
        memset(tempSymptomCode, 0, strlen(line));

    }


    printHeap(heap);

    // while(choice != 6)
    // {

    // 	scanf("%d", &choice);
    // 	switch(choice)
    // 	{
    // 		case 1:
    // 			// printf("num is 1\n");
    // 			break;
    // 		case 2:
    // 			// printf("num is 2\n");
    // 			break;
    // 		case 3:
    // 			// printf("num is 3\n");
    // 			break;
    // 		case 4:
    // 			// printf("num is 4\n");
    // 			break;
    // 		case 5:
    // 			// printf("num is 5\n");
    // 			break;
    // 		case 6:
    // 			printf("Exiting...\n");
    // 			exit(1);
    // 		default:
    // 			printf("enter a number between 1-6\n");
    // 			break;

    // 	} 
    // }

    return 0;
}
