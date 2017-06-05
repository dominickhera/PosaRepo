#include <stdio.h>
#include <stdin.h>


// char parse (FILE * dataFile)
// {
	
// }

void printFunction(void * data)
{
	printf("%s", (char *)data);
}

int compareFunction(const void *first,const void *second)
{
	int tempVal = 0;

	if(*(int *)first > *(int *)second || *(int *)first == *(int *)second)
	{
		printf("first is bigger\n");
		return 1;
		// return *(int *)first;
	}
	else
	{
		printf("second is bigger\n");
		// tempVal = *(int *)first;
		// *(int *)first = *(int *)second;
		// *(int *)second = tempVal;
		// return *(int *)first;
		return 2;
	}
}