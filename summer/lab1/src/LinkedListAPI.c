#include "LinkedListAPI.h"

List *initializeList(void (*printFunction)(void *tobePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first, const void *second))
{
    List * temp = malloc(sizeof(List));

    if(temp == NULL)
    {
        return NULL;
    }

    temp->head = NULL;
    temp->printFunction = tobePrinted;
    temp->deleteFunction = toBeDeleted;
    temp->compare = compareFunction;

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

    Node * temp; 
    Node * currentPosition;

    currentPosition = list->head;

    while(currentPosition->next != NULL)
    {
        temp = currentPosition->next;
        list->deleteFunction(currentPosition->data);
        free(currentPosition);
        currentPosition = temp;
    }

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

    List * temp;
    temp = list->head;

    if(list == NULL)
    {
        return NULL;
    }

    while(temp != NULL)
    {
        
    }



}

void printBackwards(List *list)
{

}

