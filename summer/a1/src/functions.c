#include <stdio.h>
#include <stdin.h>


char parse (FILE * dataFile)
{
	
}

void printFunction(void * data)
{
	printf("%s", (char *)data);
}

int compareFunction(const void *first,const void *second)
{
	int tempVal = 0;

	if(*(int *)first > *(int *)second || *(int *)first == *(int *)second)
	{
		return first;
	}
	else
	{
		tempVal = first;
		first = second;
		second = tempVal;
		return first;
	}
}