#include "LinkedListAPI.h"

List *initializeList(void (*printFunction)(void *tobePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first, const void *second))
{
    List * temp = malloc(sizeof(List));

    if(temp == NULL)
    {
        return NULL;
    }

    temp->head = NULL;
    temp->tail = NULL;
    temp->printFunction = tobePrinted;
    temp->deleteFunction = toBeDeleted;
    temp->compare = compareFunction;

    return temp;
}

Node *initializeNode(void *data)
{
   
   Node * temp = malloc(sizeof(Node));

   if(temp == NULL)
   {
    return NULL;
   }

   temp->next = NULL;
   temp->previous = NULL;
   temp->data = data;

   return temp;

}

void insertFront(List *list, void *toBeAdded)
{

    if(list != NULL)
    {
        toBeAdded = list->head;
        return toBeAdded;
    }
    else
    {
        return NULL;
    }

}

void insertBack(List *list, void *toBeAdded)
{

    if(list != NULL)
    {
        toBeAdded = list->tail;
        return toBeAdded;
    }
    else
    {
        return NULL;
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

    if(list != NULL)
    {
        toBeAdded = list->next;
        return toBeAdded;
    }
    else
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

    temp->tail = temp->previous;

    return temp->tail;
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

