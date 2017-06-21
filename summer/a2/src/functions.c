#include "functions.h"

void printData(void * data)
{
    printf("%s\n", (char *)data);
}

int hashData(size_t hashSize, int dataKey)
{
	return dataKey % hashSize;
}
