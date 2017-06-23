#include "functions.h"

void printData(void * data)
{
    printf("%s\n", (char *)data);
}

int hashData(size_t hashSize, char * dataKey)
{

	int tempKey = 0;

	while(*dataKey != '\0')
	{
		tempKey = tempKey + *dataKey;
		dataKey++;
	}

	return tempKey % hashSize;
}


void getPos(int * y, int * x)
{
    * y = getcury(stdscr);
    * x = getcurx(stdscr);
    return;
}
