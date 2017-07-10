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

    if(temp->type == 1)
    {
        printf("Max Heap sucessfully created with a max size of %lu\n\n", temp->maxSize);
    }
    else
    {
        printf("Min Heap Successfully created with a max size of %lu\n\n", temp->maxSize);
    }
    return temp;

}

Node *createHeapNode(void *data)
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
    temp->data = malloc(sizeof(data));
    // printf("3\n");
    if(temp == NULL)
    {
        return NULL;
    }

    temp->data = data;


    printf("Heap node Successfully created with data: %s\n", temp->data);
    return temp;
    // }
    // else
    // {
    //     printf("Heap either does not exist or has been created incorrectly.\n");
    //     return NULL;
    // }
}

void insertHeapNode(Heap *heap, void *data)
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
        Node * temp = createHeapNode(data);

        int tempSize = heap->initialSize;

        heap->initialSize++;

        while(tempSize && temp->data > heap->heapTable[getParent(tempSize)]->data)
        {
            heap->heapTable[tempSize] = heap->heapTable[getParent(tempSize)];
            tempSize = getParent(tempSize);
        }

        heap->heapTable[tempSize] = temp;

        if(heap->type == 1)
        {
            for(int i = 0; i < heap->maxSize; i++)
            {
                reheapifyMax(heap, tempSize);
            }

        }
        else
        {
            for(int i = 0; i < heap->maxSize; i++)
            {
                reheapifyMin(heap, i);
            }
        }
    }

}

void deleteMinOrMax(Heap *heap)
{
    //   tempNode = heap->rootNode
    //   heap->rootNode = the node in the "last" position in the tree //the leftmost, bottom node
    //   outOfPlacePtr = heap->rootNode  // keep track of the node that you're moving into place
    //   remove the node in the last position //after copying it into the root
    //   while ( outOfPlacePtr->data is less than either left or right child)  //or greater than for a min heap
    //   {
    //       swap outOfPlacePtr and child with greatest value
    //   }
    //   return tempNode->data
    if(heap != NULL)
    {


        if(heap->type == 1)
        {

            Node * minVal = getMinOrMax(heap);
            free(minVal);
            // printf("size b: %zu\n", heap->maxSize);
            heap->maxSize--;
            // printf("size a: %zu\n", heap->maxSize);
            reheapifyMax(heap, 0);
            printf("Min Value successfully deleted\n");
        }
        else
        {

            Node * minVal = getMinOrMax(heap);
            free(minVal);
            heap->maxSize--;
            reheapifyMin(heap, 0);
            printf("Max Value successfully deleted\n");
        }
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

void changeHeapType(Heap *heap)
{

    // printf("23\n");
    if(heap != NULL)
    {
        if(heap->type == 1)
        {

            heap->type = MIN_HEAP;
            reheapifyMin(heap, 0);
            printf("Heap type change form Max Heap to Min Heap\n\n");

        }
        else
        {
            // printf("27\n");
            // printf("minxheap before: %d\n", heap->type);
            heap->type = MAX_HEAP;

            reheapifyMax(heap, 0);
            printf("Heap type change form Min Heap to Max Heap\n\nn");
        }
    }
    else
    {
        printf("Heap either does not exist or has been created incorrectly.\n");
    }
    // printf("29\n");
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
        printf("Heap has been successfully deleted\n");
    }
    else
    {
        printf("Heap either does not exist or has been created incorrectly.\n");
    }
    // }
}

void reheapifyMax(Heap * heap, int tempSize)
{
    // parentNode = get parent node of newNode
    // while(newNode->data is greater than parentNode->data  //or less than for a min heap
    // {
    //    swap positions of newNode and Parent Node
    //    parentNode = get parent node of newNode (has changed because of the swap)
    // }

    if(heap != NULL)
    {
        int tempInt = 0;
        // printf("3\n");
        if(getLeftChild(tempSize) < heap->initialSize && heap->heapTable[getLeftChild(tempSize)]->data > heap->heapTable[tempSize]->data)
        {
            // printf("4\n");
            tempInt = getLeftChild(tempSize);
            // printf("5\n");
        }
        else
        {
            // printf("6\n");
            tempInt = tempSize;
            // printf("7\n");
        }
        // printf("8\n");
        if( getRightChild(tempSize) < heap->initialSize && heap->heapTable[getRightChild(tempSize)]->data > heap->heapTable[tempInt]->data)
        {
            // printf("9\n");
            tempInt = getRightChild(tempSize);
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
            reheapifyMax(heap, tempInt);
            // printf("16\n");

        }
    }
    else
    {

        printf("Heap either does not exist or has been created incorrectly.\n");
    }
}

void reheapifyMin(Heap * heap, int tempSize)
{
    // parentNode = get parent node of newNode
    // while(newNode->data is greater than parentNode->data  //or less than for a min heap
    // {
    //    swap positions of newNode and Parent Node
    //    parentNode = get parent node of newNode (has changed because of the swap)
    // }

    if(heap != NULL)
    {

        int tempInt = 0;
        // printf("tempSize: %d\n", tempSize);
        // printf("3\n");
        if(getLeftChild(tempSize) < heap->initialSize && heap->heapTable[getLeftChild(tempSize)]->data < heap->heapTable[tempSize]->data)
        {
            // printf("4\n");
            tempInt = getLeftChild(tempSize);
            // printf("5\n");
        }
        else
        {
            // printf("6\n");
            tempInt = tempSize;
            // printf("7\n");
        }
        // printf("8\n");
        if( getRightChild(tempSize) < heap->initialSize && heap->heapTable[getRightChild(tempSize)]->data < heap->heapTable[tempInt]->data)
        {
            // printf("9\n");
            tempInt = getRightChild(tempSize);
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
        for(int i = 0; i < heap->maxSize; i++)
        {
            printf("I: %d, Parent: %d, Left: %d, Right: %d, Data: %s\n",i + 1, getParent(i) + 1, getLeftChild(i) + 1, getRightChild(i) + 1, heap->heapTable[i]->data);
        }
    }
    else
    {

        printf("Heap either does not exist or has been created incorrectly.\n");
    }
}

