#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "functions.h"

int main()
{

	char * data[] = {"12", "23", "48", "55", "11", "42", "99"};

	Heap * heapThing = createHeap(7, 0, &free, &printData, &compareFunction);

	// printf("size: %lu\n", sizeof(data)/sizeof(data[0]));	
	for(int i = 0; i < (sizeof(data)/sizeof(data[0])); i++)
	{
		insertHeapNode(heapThing, data[i]);
	}


	for(int i = 0; i < (sizeof(data)/sizeof(data[0])); i++)
	{
		printf("heapInt[%d]: %s\n", i + 1, heapThing->heapTable[i]->data);
	}

	deleteMinOrMax(heapThing);
	// changeHeapType(heapThing);

	// printf("round 2:\n");
	// for(int i = 0; i < (sizeof(data)/sizeof(data[0])); i++)
	// {
	// 	printf("heapInt[%d]: %s\n", i + 1, heapThing->heapTable[i]->data);
	// }

	return 0;

}
