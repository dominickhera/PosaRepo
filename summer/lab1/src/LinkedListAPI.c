#include "LinkedListAPI.h"

List *initializeList(void (*printFunction)(void *tobePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first, const void *second))
{
    List * temp = malloc(sizeof(List));

    temp->head = NULL;
    temp->printFunction = void *tobePrinted;
    temp->deleteFunction = void *toBeDeleted;
    temp->compareFunction = compareFunction;

    if(temp == NULL || temp->printFunction == NULL || temp->deleteFunction == NULL || temp->compareFunction == NULL)
    {
        return NULL;
    }

    return temp;
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
    
    return list->head;

}

void *getFromBack(List *list)
{

    List * temp;
    temp = list;

    if(list == NULL)
    {
        return NULL;
    }

    temp->previous = temp->head;
    temp = temp->next;

    while(temp->next != NULL)
    {
        temp->previous = temp;
        temp = temp->next;
    }

    return temp->previous;
}

void printForward(List *list)
{

}

void printBackwards(List *list)
{

}

