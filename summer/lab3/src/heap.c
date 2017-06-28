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

}

void deleteMinOrMax(Heap *heap)
{

}

void *getMinOrMax(Heap *heap)
{

}

void changeHeapType(Heap *heap)
{

}

void deleteHeap(Heap *heap)
{

}

