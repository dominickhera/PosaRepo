#include "heap.h"

Heap *createHeap(size_t initialSize, HEAP_TYPE htype, void (*destroyDataFP)(void *data),void (*printNodeFP)(void *toBePrinted),int (*compareFP)(const void *first, const void *second))
{

	Heap * temp = malloc(sizeof(Heap) * initialSize);

	if(temp == NULL)
	{
		return NULL;
	}

	temp->HEAP_TYPE = htype;
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

	Node * temp = malloc(sizeof(Node));
	temp->data = malloc(sizeof(data));

	it(temp == NULL)
	{
		return NULL;
	}

	temp->left = NULL;
	temp->right = NULL;
	temp->parent = NULL;
	strcpy(temp->data, data);

	return temp;
}

void insertHeapNode(Heap *heap, void *data)
{
 // create a node from the data
 //    locate the next position in the heap (the left most position with no node)
 //    add the new node to the located position
 //    reheapify the heap to maintain the heap property

	heap->initialSize++;
	// int tempSize = heap->initialSize;
	Node * temp = createHeapNode(data);
	heap->heapTable[heap->initialSize] = temp;


	if(strcmp(temp->HEAP_TYPE, "MAX_HEAP") == 0)
	{
		reheapifyMax(heap, temp);
	}
	else
	{
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

	Node * temp = heap->

}

void *getMinOrMax(Heap *heap)
{

}

void changeHeapType(Heap *heap)
{

	if(strcmp(heap->HEAP_TYPE, "MAX_HEAP") == 0)
	{
		heap->HEAP_TYPE = "MIN_HEAP";
		reheapifyMin(heap, heap);
	}
	else
	{
		temp->HEAP_TYPE = "MAX_HEAP";
		reheapifyMax(heap, heap);
	}
}

void deleteHeap(Heap *heap)
{
	for(int i = 0; i < heap->initialSize; i++)
	{
		deleteMinOrMax(heap->heapTable[i]);
	}
}

