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
    temp->data = data;

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
        tempNode->data = toBeAdded;
        tempNode->next = NULL;  
        northList->northHead = tempNode;
        northList->northTail = tempNode;
    }
    else
    {
        tempNode = malloc(sizeof(Node));
        tempNode->previous = NULL;
        tempNode->data = toBeAdded;
        tempNode->next = northList->northHead;
        northList->northHead = tempNode;
    }
}

// void insertBack(NorthList *list, void *toBeAdded)
// {
//     NorthNode * tempNode = NULL;
//     tempNode = (Node*)malloc(sizeof(Node));
//     tempNode = list->head;
//     if(tempNode!= NULL)
//     {
//         tempNode = malloc(sizeof(Node));
//         tempNode->previous = list->tail;
//         tempNode->next = NULL;
//         tempNode->data = toBeAdded;
//         list->tail = tempNode; 
//     }
//     else
//     {
//         tempNode = malloc(sizeof(Node));
//         tempNode->previous = NULL;
//         tempNode->data = toBeAdded;
//         tempNode->next = NULL;
//         list->head = tempNode;
//         list->tail = tempNode;
//     }

// }


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
        tempNode->data = toBeAdded;
        tempNode->next = NULL;  
        northList->northHead = tempNode;
        northList->northTail = tempNode;
    }
    else
    {
        tempNode = malloc(sizeof(NorthNode));
        tempNode->previous = NULL;
        tempNode->data = toBeAdded;
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

void *getFromNorthFront(NorthList *northList)
{

    NorthList * temp;
    temp = northList;

    NorthNode * tempNode;
    tempNode = temp->head; 

    if(list == NULL)
    {
        printf("error\n");
    }

    return tempNode->data;

}

void *getFromNorthBack(NorthList *northList)
{

    NorthList * temp;
    temp = northList;

    NodeNode * tempNode;
    tempNode = temp->northTail;


    return tempNode->data;
}

void printNorthForward(NorthList *northList)
{

    NorthList * temp;
    temp = northList;

    NorthNode * tempNode;
    tempNode = northList->northHead;

    while(tempNode != NULL)
    {
        temp->printData(tempNode->data);
        tempNode = tempNode->next;
        tempNode->previous = tempNode;
    }
}

// void printBackwards(NorthList *northList)
// {

//     List * temp;
//     temp = list;

//     NorthNode * tempNode = NULL;
//     tempNode = list->tail;

//     while(tempNode != NULL)
//     {
//         temp->printData(tempNode->data);
//         tempNode = tempNode->previous;
//         tempNode->next = tempNode->previous;
//     }

// }


