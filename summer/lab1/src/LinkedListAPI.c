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

    if(list != NULL)
    {
        return list->head;
    }
    else
    {
        return 0;
    }

}

void insertBack(List *list, void *toBeAdded)
{

    if(list != NULL)
    {
        return list->tail;
    }
    else
    {
        return 0;
    }

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

    if(list == NULL)
    {
        return NULL;
    }



}

int deleteDataFromList(List *list, void *toBeDeleted)
{

    if(list == NULL)
    {
        return NULL;
    }

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
        list->printFunction(data);
        temp = list->next;
    }



}

void printBackwards(List *list)
{

    List * temp;
    temp = list->tail;

    if(list == NULL)
    {
        return NULL;
    }

    while(temp != NULL)
    {
        list->printFunction(data);
        temp = list->previous;
    }


}

