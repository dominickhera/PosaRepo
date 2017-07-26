#include "functions.h"

void printData(void * data)
{
    printf("%s\n", (char *)data);
}

int compareFunction(const void *first,const void *second)
{
	

	if(*(int *)first > *(int *)second || *(int *)first == *(int *)second)
	{
		return *(int *)first;
	}
	else
	{
		int tempVal = 0;
		tempVal = *(int *)first;
		*(int *)first = *(int *)second;
		*(int *)second = tempVal;
		return *(int *)first;
	}
}
