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
	char * data[] = {"Dominick", "John", "Jack", "Mary", "Sally", "Jennifer", "Bailey", "Mark"};

	HTable * hashTable = createTable(500, &hashData, &free, &printData);

	int i;
	for(i = 0; i < 8; i++)
	{
		insertData(hashTable, i, data[i]);
	}

	for(i = 0; i < 8; i++)
	{
		printf("%s\n", (char*)lookupData(hashTable, i));
	}


	destroyTable(hashTable);


	return 0;
}

