#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

void printData(void * data)
{
    printf("%s\n", (char *)data);
}

int compareFunction(const void *first,const void *second)
{
	int tempVal = 0;

	if(*(int *)first > *(int *)second || *(int *)first == *(int *)second)
	{
		return *(int *)first;
	}
	else
	{
		tempVal = *(int *)first;
		*(int *)first = *(int *)second;
		*(int *)second = tempVal;
		return *(int *)first;
	}
}

int main()
{

	printf("hi\n");

}