#include <stdio.h>
#include <stdlib.h>
#include "HashTableAPI.h"

void printData(void * data)
{
    printf("%s\n", (char *)data);
}

int hashData(size_t hashSize, int dataKey)
{
	return dataKey % hashSize;
}

int main()
{
	printf("hello world\n");

	return 0;
}

