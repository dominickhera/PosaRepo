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

    temp->destroyData = destroyData;
    temp->hashFunction = hashFunction;
    temp->printData = printData;

    return temp;

}

Node *createNode(int key, void *data)
{

    Node * temp = malloc(sizeof(Node));

    if(temp == NULL)
    {
        return NULL;
    }

    temp->key = key;
    temp->data = data;
    temp->next = NULL;

    return temp;


}

void destroyTable(HTable *hashTable)
{

    Node * temp = NULL;
    // HTable * temp2;
    // // HTable * temp2;

    while(temp != NULL)
    {
    	removeData(hashTable, temp->key);
    	temp = temp->next;
    }

    // for(int i = 0; i < hashTable->size; i++)
    // {

    //     Node * temp = removeData(hashTable, temp->key);

    //     // temp1 = Node->data;
    //     while(temp != NULL)
    //     {
    //         temp = removeData(temp, temp->key);
    //         // temp = temp->next;
    //         // temp1 = temp1->next;
    //         // free(temp2->key);
    //         // free(temp2);
    //     }

    // }

    free(hashTable);

}

void insertData(HTable *hashTable, int key, void *data)
{

    int count;

    Node * temp;

    count = hashTable->hashFunction(hashTable->size, key);

    temp = createNode(key, data);

    temp->next = hashTable->table[count];
    hashTable->table[count] = temp;

}

void removeData(HTable *hashTable, int key)
{

    int tempKey = 0;
    tempKey = hashTable->hashFunction(hashTable->size, key);
    Node * temp = hashTable->table[tempKey];

    while(temp != NULL)
    {

        if(temp->key != tempKey)
        {
            temp = temp->next;
        }
        else
        {
            free(temp->data);
            free(temp);
            temp = temp->next;
        }

    }

}

void *lookupData(HTable *hashTable, int key)
{

	int tempKey = 0;
	tempKey = hashTable->hashFunction(hashTable->size, key);

	Node * temp = hashTable->table[tempKey];

	if(temp->key == tempKey)
	{
		return temp->data;
	}
	else
	{
		return NULL;
	}


}

