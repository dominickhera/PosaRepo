#include "east.h"

EastList *initializeEastList(void (*printFunction)(void *tobePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first, const void *second))
{
    EastList * temp = NULL;
    temp = (EastList*)malloc(sizeof(EastList));

    if(temp == NULL)
    {
        return NULL;
    }

    temp->eastHead = NULL;
    temp->eastHail = NULL;
    temp->printData = printFunction;
    temp->deleteData = deleteFunction;
    temp->compare = compareFunction;

    return temp;
}

EastNode *initializeEastNode(void *data)
{

    EastNode * temp = malloc(sizeof(EastNode));

    if(temp == NULL)
    {
        return NULL;
    }

    temp->next = NULL;
    temp->previous = NULL;
    temp->data = data;

    return temp;

}

void insertEastFront(EastList *eastList, void *toBeAdded)
{
    EastNode * tempNode;
    tempNode = list->eastHead;
    
    if(tempNode == NULL)
    {
        tempNode = malloc(sizeof(EastNode));
        tempNode->previous = NULL;
        tempNode->data = toBeAdded;
        tempNode->next = NULL;  
        eastList->eastHead = tempNode;
        eastList->eastTail = tempNode;
    }
    else
    {
        tempNode = malloc(sizeof(EastNode));
        tempNode->previous = NULL;
        tempNode->data = toBeAdded;
        tempNode->next = eastList->eastHead;
        eastList->eastHead = tempNode;
    }
}

void deleteEastList(EastList *eastList)
{

    EastList * temp;
    temp = eastList;

    EastNode * tempNode;
    tempNode = eastList->eastHead;

    if(list != NULL)
    {
        while(tempNode->next != NULL)
        {
             tempNode = tempNode->next;
             free(tempNode);
        }
        free(eastList);
    } 
}

void insertEastSorted(EastList *eastList, void *toBeAdded)
{
    EastList * temp;
    temp = eastList;

    EastNode * tempNode;
    tempNode = eastList->eastHead;
    if(tempNode == NULL)
    {
        tempNode = malloc(sizeof(EastNode));
        tempNode->previous = NULL;
        tempNode->data = toBeAdded;
        tempNode->next = NULL;  
        eastList->eastHead = tempNode;
        eastList->eastTail = tempNode;
    }
    else
    {
        tempNode = malloc(sizeof(EastNode));
        tempNode->previous = NULL;
        tempNode->data = toBeAdded;
        tempNode->next = list->head;
        eastList->eastHead = tempNode;
    }

}

int deleteDataFromEastList(EastList *eastList, void *toBeDeleted)
{

    EastList * temp;
    temp = eastList;

    EastNode * tempNode;
    tempNode = eastList->eastHead;

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

void *getFromEastFront(EastList *eastList)
{

    EastList * temp;
    temp = eastList;

    EastNode * tempNode;
    tempNode = temp->eastHead; 

    if(eastList == NULL)
    {
        printf("error\n");
    }

    return tempNode->data;

}

void *getFromEastBack(EastList *eastList)
{

    EastList * temp;
    temp = eastList;

    EastNode * tempNode;
    tempNode = temp->eastTail;


    return tempNode->data;
}

void printEastForward(EastList *eastList)
{

    EastList * temp;
    temp = eastList;

    EastNode * tempNode;
    tempNode = eastList->eastHead;

    while(tempNode != NULL)
    {
        temp->printData(tempNode->data);
        tempNode = tempNode->next;
        tempNode->previous = tempNode;
    }
}


