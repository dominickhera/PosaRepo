#include "HashTableAPI.h"

HTable *createTable(size_t size, int (*hashFunction)(size_t tableSize, int key),void (*destroyData)(void *data),void (*printData)(void *toBePrinted))
{

    int i;
    HTable * temp = malloc(sizeof(HTable));

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

Node *createNode(int key, void *data)
{

    Node * temp = malloc(sizeof(Node));
    temp->data = malloc(sizeof(data)*2);


    if(temp == NULL)
    {
        return NULL;
    }

    temp->key = key;
//    strcpy(temp->data, data);
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

    if(hashTable != NULL)
    {


    count = hashTable->hashFunction(hashTable->size, key);
    Node * temp = createNode(key, data);
    temp->next = hashTable->table[count];
    hashTable->table[count] = temp;
    }
}

void removeData(HTable *hashTable, int key)
{

    int tempKey = 0;

    if (hashTable != NULL)
    {


        tempKey = hashTable->hashFunction(hashTable->size, key) % hashTable->size;

        Node * temp = hashTable->table[tempKey];
        while(temp != NULL)
        {

            if(temp->key == key)
            {
                if(temp->next != NULL)
                {
                    temp->next = temp->next->next;
                }
                //free(temp->data);
                free(temp);
                hashTable->table[tempKey] = NULL;
    //            break; 
            }
            temp = temp->next;
        }
    }



}

void *lookupData(HTable *hashTable, int key)
{

    int tempKey = 0;

    if (hashTable == NULL)
    {
        return NULL;
    }

    tempKey = hashTable->hashFunction(hashTable->size, key) % hashTable->size;

    Node * temp = hashTable->table[tempKey];
    while(temp != NULL)
    {

        if(temp->key == key)
        {
            return temp->data;
        }
        temp = temp->next;
    }

    return NULL;

}


