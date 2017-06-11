#include "HashTableAPI.h"

HTable *createTable(size_t size, int (*hashFunction)(size_t tableSize, int key),void (*destroyData)(void *data),void (*printData)(void *toBePrinted))
{

	HTable * temp = NULL;

	temp = malloc(sizeof(HTable));

	if(temp == NULL)
	{
		return NULL;
	}

	for(int i = 0; i < size; i++)
	{
		temp->table[i] = NULL;
	}

	temp->deleteData = destroyData;
	temp->hashFunc = hashFunction
	temp->printFunction = printData;

	return temp;

}

Node *createNode(int key, void *data)
{

	Node * temp;

	if(temp == NULL)
	{
		return NULL;
	}

	temp->next = NULL;

	return temp;


}

void destroyTable(HTable *hashTable)
{

	HTable * temp1;
	HTable * temp2;

	for(int i = 0; i < hashTable->size; i++)
	{

		temp1 = hashTable->data[i];
		while(temp1)
		{
			temp2 = temp1;
			temp1 = temp1->next;
			free(temp2->key);
			free(temp2);
		}

	}

	free(hashTable);

}

void insertData(HTable *hashTable, int key, void *data)
{



}

void removeData(HTable *hashTable, int key)
{

	HTable * temp;

	if(*hashTable == NULL)
	{
		removeData(&(*hashTable)->next, key);
	}
	else
	{
		if(*hashTable->key == key)
		{
			temp = *hashTable;
			*hashTable = (*hashTable)->next;
			free(temp->key);
			free(temp);
		}
	}

}

void *lookupData(HTable *hashTable, int key)
{

}

