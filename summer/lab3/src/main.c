#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "functions.h"

int main()
{

	char * data[] = {"12", "23", "41", "55", "11", "42", "41", "99"};

	Heap * heapThing = createHeap(500, "MAX_HEAP", &free, &printData, &compareFunction);

	for(int i = 0; i < 8; i++)
	{
		insertHeapNode(heapThing, data[i]);
	}

	

	return 0;

}
