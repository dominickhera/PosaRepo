#include "heap.h"

Heap *createHeap(size_t initialSize, HEAP_TYPE htype, void (*destroyDataFP)(void *data),void (*printNodeFP)(void *toBePrinted),int (*compareFP)(const void *first, const void *second))
{

    Heap * temp = malloc(sizeof(Heap) * initialSize);
    if(temp == NULL)
    {
        return NULL;
    }

    temp->heapTable = malloc(sizeof(*temp->heapTable) * initialSize);

    for(int i = 0; i < initialSize; i++)
    {
        temp->heapTable[i] = NULL;
    }

    temp->type = htype;
    temp->initialSize = 0;
    temp->maxSize = initialSize;
    temp->destroyDataFP = destroyDataFP;
    temp->printNodeFP = printNodeFP;
    temp->compareFP = compareFP;

    return temp;

}

Node *createHeapNode(int priority, void *clientID, void *symptomCode)
{
    // create a pointer to a new Node
    //     set new nodes left, right and parent pointers to NULL
    //     set the node's data to the parameter data value
    //     return the pointer to the new Node

    // Heap * tempHeap = Heap;
    // if(tempHeap != NULL)
    // {
    // printf("1\n");
    Node * temp = malloc(sizeof(Node));
    // printf("2\n");
    // temp->data = malloc(sizeof(data));
    temp->clientID = malloc(sizeof(clientID));
    temp->symptomCode = malloc(sizeof(symptomCode));
    // printf("3\n");
    if(temp == NULL)
    {
        return NULL;
    }

    // strcpy(temp->data, data);
    temp->priority = priority;
    strcpy(temp->clientID, clientID);
    strcpy(temp->symptomCode, symptomCode);
    // temp->data = data;
    // temp->clientID = clientID;
    // temp->symptomCode = symptomCode;


    // printf("Heap node Successfully created with data: %s\n", temp->data);
    return temp;
    // }
    // else
    // {
    //     printf("Heap either does not exist or has been created incorrectly.\n");
    //     return NULL;
    // }
}

void insertHeapNode(Heap *heap, int priority, void *clientID, void *symptomCode)
{
    // create a node from the data
    // locate the next position in the heap (the left most position with no node)
    // add the new node to the located position
    // reheapify the heap to maintain the heap property


    if(heap == NULL)
    {
        printf("Heap either does not exist or has been created incorrectly.\n");
        //     return NULL;  
    }
    else
    {
        Node * temp = createHeapNode(priority, clientID, symptomCode);

        int tempSize = heap->initialSize;

        heap->initialSize++;

        while(tempSize && temp->priority > heap->heapTable[getParent(tempSize)]->priority)
        {
            heap->heapTable[tempSize] = heap->heapTable[getParent(tempSize)];
            tempSize = getParent(tempSize);
        }

        heap->heapTable[tempSize] = temp;

        // printf("ID: %s, Priority: %s, Symptom Code: %s\n", temp->clientID, temp->data, temp->symptomCode);

            // for(int i = 0; i < heap->maxSize; i++)
            // {
                reheapifyMin(heap, 0);
            // }

    }

}

void deleteMinOrMax(Heap *heap)
{

    if(heap != NULL)
    {

            Node * minVal = getMinOrMax(heap);
            free(minVal);
            heap->maxSize--;
            reheapifyMin(heap, 0);
            // printf("Max Value successfully deleted\n");
    }
    else
    {
        printf("Heap either does not exist or has been created incorrectly.\n");
    }

}

void *getMinOrMax(Heap *heap)
{
    if(heap == NULL)
    {
        return heap->heapTable[heap->maxSize - 1];
    }
    else
    {
        printf("Heap either does not exist or has been created incorrectly.\n");
        return NULL;
    }
}


void deleteHeap(Heap *heap)
{
    if(heap != NULL)
    {


        while(heap->maxSize != 1)
        {

            deleteMinOrMax(heap);

        }

        heap->maxSize--;
        free(heap->heapTable);
        // printf("Heap has been successfully deleted\n");
    }
    else
    {
        printf("Heap either does not exist or has been created incorrectly.\n");
    }
    // }
}

void reheapifyMin(Heap * heap, int tempSize)
{

    if(heap != NULL)
    {
    
        int tempInt = 0;
        // printf("tempSize1: %d\n", tempSize);
        // printf("3\n");
        if(getLeftChild(tempSize) < heap->initialSize && heap->heapTable[getLeftChild(tempSize)]->priority < heap->heapTable[tempSize]->priority)
        {
            // printf("4\n");
            tempInt = getLeftChild(tempSize);
            // printf("tempSize2: %d\n", tempSize);
            // printf("5\n");
        }
        else
        {
            // printf("6\n");
            tempInt = tempSize;
            // printf("tempSize3: %d\n", tempSize);
            // printf("7\n");
        }
        // printf("8\n");
        if(getRightChild(tempSize) < heap->initialSize && heap->heapTable[getRightChild(tempSize)]->priority < heap->heapTable[tempInt]->priority)
        {
            // printf("9\n");
            tempInt = getRightChild(tempSize);
            // printf("tempSize: %d\n", tempSize);
            // printf("10\n");
        }
        // printf("11\n");
        if(tempInt != tempSize)
        {

            Node * swapNode = heap->heapTable[tempSize];
            // printf("13\n");

            heap->heapTable[tempSize] = heap->heapTable[tempInt];
            // printf("14\n");

            heap->heapTable[tempInt] = swapNode;
            // printf("15\n");
            reheapifyMin(heap, tempInt);
        }
    }
    else
    {
        printf("Heap either does not exist or has been created incorrectly.\n");
    }
}

int getParent(int tempInt)
{

    return ((tempInt - 1)/2);

}

int getLeftChild(int tempInt)
{

    return ((tempInt * 2) + 1);

}

int getRightChild(int tempInt)
{

    return ((tempInt * 2) + 2);

}

void printHeap(Heap * heap)
{
    if(heap != NULL)
    {
        for(int i = 0; i < heap->initialSize; i++)
        {
            printf("I: %d ClientID: %s, Priority: %d, Symptom Code: %s\n",i + 1, heap->heapTable[i]->clientID, heap->heapTable[i]->priority, heap->heapTable[i]->symptomCode);
        }
    }
    else
    {

        printf("Heap either does not exist or has been created incorrectly.\n");
    }
}

