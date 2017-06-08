#include "HashTableAPI.h"

HTable *createTable(size_t size, int (*hashFunction)(size_t tableSize, int key),void (*destroyData)(void *data),void (*printData)(void *toBePrinted))
{

}

Node *createNode(int key, void *data)
{

}

void destroyTable(HTable *hashTable)
{

}

void insertData(HTable *hashTable, int key, void *data)
{

}

void removeData(HTable *hashTable, int key)
{

}

void *lookupData(HTable *hashTable, int key)
{

}

