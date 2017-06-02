#include "west.h"

WestList *initializeWestList(void (*printFunction)(void *tobePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first, const void *second))
{
    WestList * temp = NULL;
    temp = (WestList*)malloc(sizeof(WestList));

    if(temp == NULL)
    {
        return NULL;
    }

    temp->head = NULL;
    temp->tail = NULL;
    temp->printData = printFunction;
    temp->deleteData = deleteFunction;
    temp->compare = compareFunction;

    return temp;
}

WestNode *initializeWestNode(void *data)
{

    WestNode * temp = malloc(sizeof(WestNode));

    if(temp == NULL)
    {
        return NULL;
    }

    temp->next = NULL;
    temp->previous = NULL;
    temp->data = data;

    return temp;

}

void insertWestFront(WestList *westList, void *toBeAdded)
{
    WestNode * tempNode;
    tempNode = westList->westHead;
    
    if(tempNode == NULL)
    {
        tempNode = malloc(sizeof(WestNode));
        tempNode->previous = NULL;
        tempNode->data = toBeAdded;
        tempNode->next = NULL;  
        westList->westHead = tempNode;
        westList->westTail = tempNode;
    }
    else
    {
        tempNode = malloc(sizeof(WestNode));
        tempNode->previous = NULL;
        tempNode->data = toBeAdded;
        tempNode->next = list->head;
        list->head = tempNode;
    }
}

void deleteWestList(WestList *westList)
{

    WestList * temp;
    temp = westList;

    WestNode * tempNode;
    tempNode = westList->westHead;

    if(list != NULL)
    {
        while(tempNode->next != NULL)
        {
             tempNode = tempNode->next;
             free(tempNode);
        }
        free(westList);
    } 
}

void insertWestSorted(WestList *list, void *toBeAdded)
{
    WestList * temp;
    temp = westList;

    WestNode * tempNode;
    tempNode = westList->westHead;
    if(tempNode == NULL)
    {
        tempNode = malloc(sizeof(WestNode));
        tempNode->previous = NULL;
        tempNode->data = toBeAdded;
        tempNode->next = NULL;  
        westList->westHead = tempNode;
        westList->westTail = tempNode;
    }
    else
    {
        tempNode = malloc(sizeof(WestNode));
        tempNode->previous = NULL;
        tempNode->data = toBeAdded;
        tempNode->next = westList->westHead;
        westList->westHead = tempNode;
    }

}

int deleteDataFromWestList(WestList *westList, void *toBeDeleted)
{

    WestList * temp;
    temp = westList;

    WestNode * tempNode;
    tempNode = westList->westHead;

    while(tempNode->next != NULL)
    {
        if(tempNode->data == toBeDeleted)
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

void *getFromWestFront(WestList *westList)
{

    WestList * temp;
    temp = westList;

    WestNode * tempNode;
    tempNode = temp->westHead; 

    if(westList == NULL)
    {
        printf("error\n");
    }

    return tempNode->data;

}

void *getFromWestBack(WestList *westList)
{

    WestList * temp;
    temp = westList;

    WestNode * tempNode;
    tempNode = temp->westTail;


    return tempNode->data;
}

void printWestForward(WestList *westList)
{

    WestList * temp;
    temp = westList;

    WestNode * tempNode;
    tempNode = westList->westHead;

    while(tempNode != NULL)
    {
        temp->printData(tempNode->data);
        tempNode = tempNode->next;
        tempNode->previous = tempNode;
    }
}


