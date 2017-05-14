#include "LinkedListAPI.h"

List *initializeList(void (*printFunction)(void *tobePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first, const void *second))
{

}

Node *initializeNode(void *data)
{

}

void insertFront(List *list, void *toBeAdded)
{

}

void insertBack(List *list, void *toBeAdded)
{

}

void deleteList(Life *list)
{

}

void insertSorted(List *list, void *toBeAdded)
{

}

int deleteDataFromList(List *list, void *toBeDeleted)
{

}

void *getFromFront(List *list)
{

    if(list == NULL)
    {
        return NULL;
    }
    
    return list;

}

void *getFromBack(List *list)
{

    List * temp;
    temp = list;

    while(temp->next != NULL)
    {
        temp = temp->next;
    }

    return temp;
}

void printForward(List *list)
{

}

void printBackwards(List *list)
{

}

