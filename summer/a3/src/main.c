#include "heap.h"
#include "functions.h"

int main(int argc, char* argv[])
{

    int choice = 0;
    char * fileName = argv[1];
    char line[256];
    char tempID[256];
    char tempPriority[50];
    char tempSymptomCode[50];
    int parseCount = 0;
    int cycle = 0;
    int cycleCheck = 0;
    FILE *fp;
    FILE *fo;

    if(argc != 2)
    {
        printf("wrong amount of arguements entered\n");
        exit(1);
    }


    fp = fopen(fileName, "r");
    fo = fopen("./assets/report.txt", "w");

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

    fclose(fp);

    // printHeap(heap);

    while(choice != 6)
    {

        printf("\n1.add new client\n2.remove old client\n3.cycle through heap\n4.print list\n5.save\n6.exit\n\n/> ");
    	scanf("%d", &choice);
    	switch(choice)
    	{
    		case 1:
                memset(tempID, 0, strlen(line));
                memset(tempPriority, 0, strlen(line));
                memset(tempSymptomCode, 0, strlen(line));
    			printf("enter client ID: ");
                scanf("%s", tempID);
                printf("enter Priority (1-5): ");
                scanf("%s", tempPriority);
                printf("enter symptom code: ");
                scanf("%s", tempSymptomCode);
                insertHeapNode(heap, atoi(tempPriority), tempID, tempSymptomCode);
                // printf("heapID: %d, ID: %s, Priority: ")
    			break;
    		case 2:
                memset(tempID, 0, strlen(line));
    			// printf("remove old client\n");
                printf("enter client ID: ");
                scanf("%s", tempID);
                deleteHeapNode(heap, tempID);
    			break;
    		case 3:
    			// printf("go through heap from top to bottom\n");
                // if(cycle >= heap->initialSize)
                // {
                    cycleCheck = 0;
                // }
                while(cycleCheck != 3)
                {
                    printf("<(1):(2)> Exit(3)\n\n/> ");
                    scanf("%d", &cycleCheck);
                switch(cycleCheck)
                {
                    // printf("<(1):(2)> Exit(3)\n\n");
                    // scanf("%d", &cycleCheck);
                    case 1:
                        cycle--;
                        if(cycle < 0)
                        {
                            cycle = heap->initialSize - 1;
                        }
                        // printf("cycle: %d\n", cycle);
                        printf("[%d/%zu]: Client ID: %s, Priority: %d, Symptom Code: %s\n", cycle + 1, heap->initialSize, heap->heapTable[cycle]->clientID, heap->heapTable[cycle]->priority, heap->heapTable[cycle]->symptomCode);
                        // cycle--;
                        break;
                    case 2:
                        cycle++;
                        if(cycle > heap->initialSize - 1)
                        {
                            cycle = 0;
                        }
                        // printf("cycle: %d\n", cycle);
                        printf("[%d/%zu]: Client ID: %s, Priority: %d, Symptom Code: %s\n", cycle + 1, heap->initialSize, heap->heapTable[cycle]->clientID, heap->heapTable[cycle]->priority, heap->heapTable[cycle]->symptomCode);
                        // cycle++;
                        break;
                    case 3:
                        break;
                    default:
                        break;
                }
            }
                // printf("[%d/%zu]: Client ID: %s, Priority: %d, Symptom Code: %s\n", cycle + 1, heap->initialSize, heap->heapTable[cycle]->clientID, heap->heapTable[cycle]->priority, heap->heapTable[cycle]->symptomCode);
    			// cycle++;
                break;
    		case 4:
    			// printf("printing list\n");
                printHeap(heap, fo, 2);
    			break;
    		case 5:
                // char tempMaxorMin[256];
    			printf("heaipfy\n");
                reheapifyMin(heap, 0);
                // Node * tempMaxorMin = getMaxorMin(heap);
                // printf("temp: %s\n", tempMaxorMin->clientID);
                // getMaxorMin(heap);

    			break;
    		case 6:
                fp = fopen(fileName, "w");
    			printf("Exiting...\n");
                fprintf(fo, "Client List (in Order Processed)\n\n");
                printHeap(heap, fo, 1);
                printHeap(heap, fp, 0);
                deleteHeap(heap);
                fclose(fp);
                fclose(fo);
    			exit(1);
    		default:
    			printf("enter a number between 1-6\n");
    			break;

    	} 
    }

    return 0;
}
