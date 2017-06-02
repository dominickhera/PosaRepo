#include "south.h"

SouthList *initializeSouthList(void (*printFunction)(void *tobePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first, const void *second))
{
    SouthList * temp = NULL;
    temp = (SouthList*)malloc(sizeof(SouthList));

    if(temp == NULL)
    {
        return NULL;
    }

    temp->southHead = NULL;
    temp->southTail = NULL;
    temp->printData = printFunction;
    temp->deleteData = deleteFunction;
    temp->compare = compareFunction;

    return temp;
}

SouthNode *initializeSouthNode(void *data)
{

    SouthNode * temp = malloc(sizeof(SouthNode));

    if(temp == NULL)
    {
        return NULL;
    }

    temp->next = NULL;
    temp->previous = NULL;
    temp->data = data;

    return temp;

}

void insertSouthFront(SouthList *southList, void *toBeAdded)
{
    SouthNode * tempNode;
    tempNode = southList->southHead;
    
    if(tempNode == NULL)
    {
        tempNode = malloc(sizeof(SouthNode));
        tempNode->previous = NULL;
        tempNode->data = toBeAdded;
        tempNode->next = NULL;  
        southList->southHead = tempNode;
        southList->southTail = tempNode;
    }
    else
    {
        tempNode = malloc(sizeof(SouthNode));
        tempNode->previous = NULL;
        tempNode->data = toBeAdded;
        tempNode->next = southList->southHead;
        southList->southHead = tempNode;
    }
}

void deleteSouthList(SouthList *southList)
{

    SouthList * temp;
    temp = southList;

    SouthNode * tempNode;
    tempNode = southList->southHead;

    if(southList != NULL)
    {
        while(tempNode->next != NULL)
        {
             tempNode = tempNode->next;
             free(tempNode);
        }
        free(southList);
    } 
}

void insertSouthSorted(SouthList *southList, void *toBeAdded)
{
    SouthList * temp;
    temp = southList;

    SouthNode * tempNode;
    tempNode = southList->southHead;
    if(tempNode == NULL)
    {
        tempNode = malloc(sizeof(SouthNode));
        tempNode->previous = NULL;
        tempNode->data = toBeAdded;
        tempNode->next = NULL;  
        southList->southHead = tempNode;
        southList->southTail = tempNode;
    }
    else
    {
        tempNode = malloc(sizeof(SouthNode));
        tempNode->previous = NULL;
        tempNode->data = toBeAdded;
        tempNode->next = list->head;
        southList->southHead = tempNode;
    }

}

int deleteDataFromSouthList(SouthList *southList, void *toBeDeleted)
{

    SouthList * temp;
    temp = southList;

    SouthNode * tempNode;
    tempNode = southList->southHead;

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

void *getFromSouthFront(SouthList *southList)
{

    SouthList * temp;
    temp = southList;

    SouthNode * tempNode;
    tempNode = temp->southHead; 

    if(southList == NULL)
    {
        printf("error\n");
    }

    return tempNode->data;

}

void *getFromSouthBack(SouthList *southList)
{

    SouthList * temp;
    temp = southList;

    SouthNode * tempNode;
    tempNode = temp->southTail;


    return tempNode->data;
}

void printSouthForward(SouthList *southList)
{

    SouthList * temp;
    temp = southList;

    SouthNode * tempNode;
    tempNode = southList->southHead;

    while(tempNode != NULL)
    {
        temp->printData(tempNode->data);
        tempNode = tempNode->next;
        tempNode->previous = tempNode;
    }
}


