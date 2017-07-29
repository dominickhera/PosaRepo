#include "functions.h"

void printData(void * data)
{
    printf("%s\n", (char *)data);
}

int compareFunction(void *first, void *second)
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

void *copyFunction(void *toBeCopy)
{
	printf("this is supposed to copy stuff i think\n");

	return toBeCopy;
}
