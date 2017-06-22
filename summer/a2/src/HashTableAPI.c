#include "HashTableAPI.h"

HTable *createTable(size_t size, int (*hashFunction)(size_t tableSize, char * key),void (*destroyData)(void *data),void (*printData)(void *toBePrinted))
{

    int i;
    HTable * temp = malloc(sizeof(*temp));

    if(temp == NULL)
    {
        return NULL;
    }

    temp->table = malloc(sizeof(*temp->table) * size);

    for(i = 0; i < size; i++)
    {
        temp->table[i] = NULL;
    }

    temp->size = size;
    temp->destroyData = destroyData;
    temp->hashFunction = hashFunction;
    temp->printData = printData;

    return temp;

}

Node *createNode(char * key, void *data)
{

    Node * temp = malloc(sizeof(*temp));

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

    while(temp != NULL)
    {
        removeData(hashTable, temp->key);
        temp = temp->next;
    }

    free(hashTable);

}

void insertData(HTable *hashTable, char * key, void *data)
{

    if(hashTable != NULL)
    {
        int count = 0;
        count = hashTable->hashFunction(hashTable->size, key);
        Node * temp = createNode(key, data);
        temp->next = hashTable->table[count];
        hashTable->table[count] = temp;
    }
}

void removeData(HTable *hashTable, char * key)
{

    if (hashTable != NULL)
    {
        int tempKey = 0;
        tempKey = hashTable->hashFunction(hashTable->size, key);
        Node * temp = hashTable->table[tempKey];

        while(temp != NULL)
        {
            if(strcmp(temp->key, key) == 0) 
            {
                if(temp->next != NULL)
                {
                    temp->next = temp->next->next;
                }

                free(temp);
                break;
            }

            temp = temp->next;
        }
    }
}

void *lookupData(HTable *hashTable, char * key)
{

    int tempKey = 0;

    if (hashTable == NULL)
    {
        return NULL;
    }

    tempKey = hashTable->hashFunction(hashTable->size, key);

    Node * temp = hashTable->table[tempKey];
    if(temp == NULL)
    {
        // printf("\n\nYou don't seem to have any account with this website/program...\n\n");
        return NULL;
    }
    // while(temp != NULL)
    // {

    if(strcmp(temp->key, key) == 0)
    {
        if(strcmp(temp->data, "\0") == 0)
        {
            return NULL;
        }
        else
        {
            return temp->data;
        }
    }
    else
    {
        return NULL;
    }

    // temp = temp->next;
    // }

    // return NULL;

}


