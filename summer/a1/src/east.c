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
    temp->eastTail = NULL;
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
    // temp->previous = NULL;
    temp->eastData = data;

    return temp;

}

void insertEastFront(EastList *eastList, void *toBeAdded)
{
    EastNode * tempNode;
    tempNode = eastList->eastHead;
    
    if(tempNode == NULL)
    {
        tempNode = malloc(sizeof(EastNode));
        // tempNode->previous = NULL;
        tempNode->eastData = toBeAdded;
        tempNode->next = NULL;  
        eastList->eastHead = tempNode;
        eastList->eastTail = tempNode;
    }
    else
    {
        tempNode = malloc(sizeof(EastNode));
        // tempNode->previous = NULL;
        tempNode->eastData = toBeAdded;
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

    if(eastList != NULL)
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
        // tempNode->previous = NULL;
        tempNode->eastData = toBeAdded;
        tempNode->next = NULL;  
        eastList->eastHead = tempNode;
        eastList->eastTail = tempNode;
    }
    else
    {
        tempNode = malloc(sizeof(EastNode));
        // tempNode->previous = NULL;
        tempNode->eastData = toBeAdded;
        tempNode->next = eastList->eastHead;
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
        if(tempNode->eastData == toBeDeleted)
        {
            if(tempNode->next != NULL)
            {
                tempNode->next = tempNode->next->next;
            } 

            // if(tempNode->previous != NULL)
            // {
            //     tempNode->previous->next = tempNode->next;
            // }
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

    return tempNode->eastData;

}

void *getFromEastBack(EastList *eastList)
{

    EastList * temp;
    temp = eastList;

    EastNode * tempNode;
    tempNode = temp->eastTail;


    return tempNode->eastData;
}

void printEastForward(EastList *eastList)
{

    EastList * temp;
    temp = eastList;

    EastNode * tempNode;
    tempNode = eastList->eastHead;

    while(tempNode != NULL)
    {
        temp->printData(tempNode->eastData);
        tempNode = tempNode->next;
        // tempNode->previous = tempNode;
    }
}


