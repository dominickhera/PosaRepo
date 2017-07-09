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
    // temp->lastPosition = NULL;
    temp->initialSize = 0;
    temp->maxSize = initialSize;
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

    // printf("1\n");
    Node * temp = malloc(sizeof(Node));
    // printf("2\n");
    temp->data = malloc(sizeof(data));
    // printf("3\n");
    if(temp == NULL)
    {
        return NULL;
    }
    // printf("4\n");
    // temp->left = NULL;
    // printf("5\n");
    // temp->right = NULL;
    // printf("6\n");
    // temp->parent = NULL;
    // printf("7\n");
    temp->data = data;
    // printf("8\n");
    // strcpy(temp->data, data);
    // printf("8\n");
    return temp;
}

void insertHeapNode(Heap *heap, void *data)
{
    // create a node from the data
    // locate the next position in the heap (the left most position with no node)
    // add the new node to the located position
    // reheapify the heap to maintain the heap property

    // printf("9\n");
    // printf("10\n");
    
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
        // for(int i = 0; i < heap->maxSize; i++)
        // {
            reheapifyMax(heap, tempSize);
        // }
    }
    else
    {
        // for(int i = 0; i < heap->maxSize; i++)
        // {
            reheapifyMin(heap, tempSize);
        // }
    	// printf("butts");
    }

    printf("data: %s\n", temp->data);

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

    for(int i = 0; i < heap->maxSize; i++)
    {
        printf("I: %d, P: %d, L: %d, R: %d\n",i + 1, getParent(i), getLeftChild(i), getRightChild(i));
    }

}

// void *getMinOrMax(Heap *heap)
// {

	// if(strcmp(heap->type, "MAX_HEAP") == 0)
 //    {
 //    	if(getLeftChild())
 //    }
 //    else
 //    {
    	
 //    	printf("butts");
 //    }	

// }

void changeHeapType(Heap *heap)
{

    // printf("23\n");
    if(heap->type == 0)
    {
        // printf("24\n");
        heap->type = 0;
        // printf("25\n");
        for(int i = 0; i < heap->maxSize; i++)
        {
            reheapifyMin(heap, i);
        }
        // reheapifyMin(heap, heap->heapTable[0]);
        // printf("26\n");
    }
    else
    {
        // printf("27\n");
        heap->type = 1;
        // printf("28\n");
        // for(int i = 0; i < heap->maxSize; i++)
        // {
            reheapifyMax(heap, heap->maxSize);
        // }
        // reheapifyMax(heap, heap->heapTable[heap->initialSize]);
    }
    // printf("29\n");
}

void deleteHeap(Heap *heap)
{
    for(int i = 0; i < heap->initialSize; i++)
    {
        // deleteMinOrMax(heap->heapTable[i]);
    }
}

void reheapifyMax(Heap * heap, int tempSize)
{
    // parentNode = get parent node of newNode
    // while(newNode->data is greater than parentNode->data  //or less than for a min heap
    // {
    //    swap positions of newNode and Parent Node
    //    parentNode = get parent node of newNode (has changed because of the swap)
    // }

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

void reheapifyMin(Heap * heap, int tempSize)
{
    // parentNode = get parent node of newNode
    // while(newNode->data is greater than parentNode->data  //or less than for a min heap
    // {
    //    swap positions of newNode and Parent Node
    //    parentNode = get parent node of newNode (has changed because of the swap)
    // }

   int tempInt = 0;
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

int getParent(int tempInt)
{

    return ((tempInt - 1)/2);

}

int getLeftChild(int tempInt)
{

    return ((tempInt * 2) + 2);

}

int getRightChild(int tempInt)
{

    return ((tempInt * 2) + 3);

}

