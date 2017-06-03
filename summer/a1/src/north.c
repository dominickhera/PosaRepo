#include "north.h"

NorthList *initializeNorthList(void (*printFunction)(void *tobePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first, const void *second))
{
    NorthList * temp = NULL;
    temp = (NorthList*)malloc(sizeof(NorthList));

    if(temp == NULL)
    {
        return NULL;
    }

    temp->northHead = NULL;
    temp->northTail = NULL;
    temp->printData = printFunction;
    temp->deleteData = deleteFunction;
    temp->compare = compareFunction;

    return temp;
}

NorthNode *initializeNorthNode(void *data)
{

    NorthNode * temp = malloc(sizeof(NorthNode));

    if(temp == NULL)
    {
        return NULL;
    }

    temp->next = NULL;
    temp->previous = NULL;
    temp->northData = data;

    return temp;

}

void insertFront(NorthList *northList, void *toBeAdded)
{
    NorthNode * tempNode;
    tempNode = northList->northHead;
    
    if(tempNode == NULL)
    {
        tempNode = malloc(sizeof(NorthNode));
        tempNode->previous = NULL;
        tempNode->northData = toBeAdded;
        tempNode->next = NULL;  
        northList->northHead = tempNode;
        northList->northTail = tempNode;
    }
    else
    {
        tempNode = malloc(sizeof(NorthNode));
        tempNode->previous = NULL;
        tempNode->northData = toBeAdded;
        tempNode->next = northList->northHead;
        northList->northHead = tempNode;
    }
}


void deleteNorthList(NorthList *northList)
{

    NorthList * temp;
    temp = northList;

    NorthNode * tempNode;
    tempNode = northList->northHead;

    if(northList != NULL)
    {
        while(tempNode->next != NULL)
        {
             tempNode = tempNode->next;
             free(tempNode);
        }
        free(northList);
    } 
}

void insertNorthSorted(NorthList *northList, void *toBeAdded)
{
    NorthList * temp;
    temp = northList;

    NorthNode * tempNode;
    tempNode = northList->northHead;
    if(tempNode == NULL)
    {
        tempNode = malloc(sizeof(NorthNode));
        tempNode->previous = NULL;
        tempNode->northData = toBeAdded;
        tempNode->next = NULL;  
        northList->northHead = tempNode;
        northList->northTail = tempNode;
    }
    else
    {
        tempNode = malloc(sizeof(NorthNode));
        tempNode->previous = NULL;
        tempNode->northData = toBeAdded;
        tempNode->next = northList->northHead;
        northList->northHead = tempNode;
    }

}

int deleteDataFromNorthList(NorthList *northList, void *toBeDeleted)
{

    NorthList * temp;
    temp = northList;

    NorthNode * tempNode;
    tempNode = northList->northHead;

    while(tempNode->next != NULL)
    {
        if(tempNode->northData == toBeDeleted)
        {
            if(tempNode->next != NULL)
            {
                tempNode->next->previous = tempNode->previous;
            } 

            if(tempNode->previous != NULL)
            {
                tempNode->previous->next = tempNode->next;
            }
            free(tempNode);
        }
        tempNode = tempNode->next;
    }

    return 0;
}

void *getFromNorthFront(NorthList *northList)
{

    NorthList * temp;
    temp = northList;

    NorthNode * tempNode;
    tempNode = temp->northHead; 

    if(northList == NULL)
    {
        printf("error\n");
    }

    return tempNode->northData;

}

void *getFromNorthBack(NorthList *northList)
{

    NorthList * temp;
    temp = northList;

    NorthNode * tempNode;
    tempNode = temp->northTail;


    return tempNode->northData;
}

void printNorthForward(NorthList *northList)
{

    NorthList * temp;
    temp = northList;

    NorthNode * tempNode;
    tempNode = northList->northHead;

    while(tempNode != NULL)
    {
        temp->printData(tempNode->northData);
        tempNode = tempNode->next;
        tempNode->previous = tempNode;
    }
}


