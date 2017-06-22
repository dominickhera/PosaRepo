#include "HashTableAPI.h"

HTable *createTable(size_t size, int (*hashFunction)(size_t tableSize, char * key),void (*destroyData)(void *data),void (*printData)(void *toBePrinted))
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

Node *createNode(char * key, void *data)
{
    // printf("p1\n");
    Node * temp = malloc(sizeof(Node));
    temp->key = malloc(sizeof(key)*2);
    temp->data = malloc(sizeof(data)*2);
    // printf("p2\n");
    if(temp == NULL)
    {
        return NULL;
    }

    // printf("p3\n");
    strcpy(temp->key, key);
    // temp->key = key;
    // printf("p4\n");
    // printf("data before insert: %s\n", (char *) temp->data);
    strcpy(temp->data, data);
    // temp->data = data; 
    // printf("data before insert: %s\n", (char *) temp->data);
    // printf("p5\n");
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

        // printf("key: %s, data:%s\n", (char *) temp->key, (char *) temp->data);
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
                hashTable->table[tempKey] = NULL;
                break;
            }

            temp = temp->next;
        }
    }
}

void *lookupData(HTable *hashTable, char * key)
{
    // printf("wtf\n");
    if (hashTable == NULL)
    {
        return NULL;
    }

    // printf("1\n");
    int tempKey = 0;
    // printf("2\n");
    tempKey = hashTable->hashFunction(hashTable->size, key);
    // printf("3\n");
    // printf("tempkey69: %d\n", tempKey);
    Node * temp = hashTable->table[tempKey];
    // printf("4\n");
    if(temp == NULL || key == NULL || temp->data == NULL)
    {
        // printf("5\n");
        return NULL;
    }

    // printf("6\n");
    while(temp != NULL)
    {
        // printf("key: %s\n", (char *)temp->key);
        // printf("7\n");
        if(strcmp(temp->key, key) == 0)
        {
            // printf("8\n");
            return temp->data;
            break;
        }
        temp = temp->next;
        // printf("9\n");

    }
    // printf("10\n");
    return NULL;
}

void printList(HTable * hashTable)
{
    // if (hashTable == NULL)
    // {
    //     return NULL;
    // }

    for(int i = 0; i < hashTable->size; i++)
    {
        // printf("i: %d\n", i);
        Node * temp = hashTable->table[i];
        // printf("4\n");
        // if(temp == NULL || key == NULL || temp->data == NULL)
        // {
        //     // printf("5\n");
        //     return NULL;
        // }

        // printf("6\n");
        while(temp != NULL)
        {
            printf("i[%d], key: %s, data: %s\n", i, (char *)temp->key, (char *)temp->data);

            temp = temp->next;

        }
    }
}


