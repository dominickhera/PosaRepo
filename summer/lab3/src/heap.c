#include "heap.h"

Heap *createHeap(size_t initialSize, void *htype, void (*destroyDataFP)(void *data),void (*printNodeFP)(void *toBePrinted),int (*compareFP)(const void *first, const void *second))
{

    Heap * temp = malloc(sizeof(Heap) * initialSize);
    if(temp == NULL)
    {
        return NULL;
    }
    // temp->HEAP_TYPE = htype;
    // strcpy(temp->type, htype);
    temp->type = htype;
    temp->initialSize = initialSize;
    temp->destroyDataFP = destroyDataFP;
    temp->printNodeFP = printNodeFP;
    temp->compareFP = compareFP;

    return temp;

}

Node *createHeapNode(void *data)
{
    // create a pointer to a new Node
    //     set new nodes left, right and parent pointers to NULL
    //     set the node's data to the parameter data value
    //     return the pointer to the new Node

	printf("1\n");
    Node * temp = malloc(sizeof(Node));
    printf("2\n");
    temp->data = malloc(sizeof(data));
    printf("3\n");
    if(temp == NULL)
    {
        return NULL;
    }
    printf("4\n");
    temp->left = NULL;
    printf("5\n");
    temp->right = NULL;
    printf("6\n");
    temp->parent = NULL;
    printf("7\n");
    // temp->data = data;
    // printf("8\n");
    strcpy(temp->data, data);
    printf("8\n");
    return temp;
}

void insertHeapNode(Heap *heap, void *data)
{
    // create a node from the data
    //    locate the next position in the heap (the left most position with no node)
    //    add the new node to the located position
    //    reheapify the heap to maintain the heap property
	printf("9\n");
    // heap->initialSize++;
    printf("10\n");
    int tempSize = heap->initialSize++;
    Node * temp = createHeapNode(data);
    printf("11\n");
    // heap->heapTable[tempSize	] = temp;
    printf("12\n");


    if(strcmp((char *)heap->type, "MAX_HEAP") == 0)
    {
    	printf("13\n");
        reheapifyMax(heap, temp);
    }
    else
    {
    	printf("14\n");
        reheapifyMin(heap, temp);
    }
}

void deleteMinOrMax(Heap *heap)
{
    // tempNode = heap->rootNode
    //   heap->rootNode = the node in the "last" position in the tree //the leftmost, bottom node
    //   outOfPlacePtr = heap->rootNode  // keep track of the node that you're moving into place
    //   remove the node in the last position //after copying it into the root
    //   while ( outOfPlacePtr->data is less than either left or right child)  //or greater than for a min heap
    //   {
    //       swap outOfPlacePtr and child with greatest value
    //   }
    //   return tempNode->data

    // Node * temp = heap->

}

// void *getMinOrMax(Heap *heap)
// {

// }

void changeHeapType(Heap *heap)
{

    if(strcmp((char *)heap->type, "MAX_HEAP") == 0)
    {
        strcpy(heap->type, "MIN_HEAP");
        reheapifyMin(heap, heap->heapTable[0]);
    }
    else
    {
        strcpy(heap->type, "MAX_HEAP");
        reheapifyMax(heap, heap->heapTable[heap->initialSize]);
    }
}

void deleteHeap(Heap *heap)
{
    for(int i = 0; i < heap->initialSize; i++)
    {
        deleteMinOrMax(heap->heapTable[i]);
    }
}

void reheapifyMax(Heap * heap, Node * newNode)
{
    // parentNode = get parent node of newNode
    // while(newNode->data is greater than parentNode->data  //or less than for a min heap
    // {
    //    swap positions of newNode and Parent Node
    //    parentNode = get parent node of newNode (has changed because of the swap)
    // }
	printf("15\n");
    Node * swapVar = newNode;
    printf("16\n");
    Node * tempParent = newNode->parent;
    printf("17\n");

    while(newNode->data > tempParent->data)
    {
    	printf("18\n");
        swapVar = newNode;
        printf("19\n");
        newNode = tempParent;
        printf("20\n");
        tempParent = swapVar;
        printf("21\n");
        tempParent = newNode->parent;
        printf("22\n");
    }
    printf("23\n");
}

void reheapifyMin(Heap * heap, Node * newNode)
{
    // parentNode = get parent node of newNode
    // while(newNode->data is greater than parentNode->data  //or less than for a min heap
    // {
    //    swap positions of newNode and Parent Node
    //    parentNode = get parent node of newNode (has changed because of the swap)
    // }

    Node * swapVar = newNode;
    Node * tempParent = newNode->parent;


    while(newNode->data < tempParent->data)
    {

        swapVar = newNode;
        newNode = tempParent;
        tempParent = swapVar;
        tempParent = newNode->parent;

    }
}

