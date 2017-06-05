#include "west.h"
#include "functions.h"

WestList *initializeWestList(void (*printFunction)(void *tobePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first, const void *second))
{
    WestList * temp = NULL;
    temp = (WestList*)malloc(sizeof(WestList));

    if(temp == NULL)
    {
        return NULL;
    }

    temp->westHead = NULL;
    temp->westTail = NULL;
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
    // temp->previous = NULL;
    temp->westData = data;

    return temp;

}

void insertWestFront(WestList *westList, void *toBeAdded, void *timeToBeAdded)
{
    WestNode * tempNode;
    tempNode = westList->westHead;
    
    if(tempNode == NULL)
    {
        tempNode = malloc(sizeof(WestNode));
        // tempNode->previous = NULL;
        tempNode->westData = toBeAdded;
        tempNode->westTimeData = timeToBeAdded;
        tempNode->next = NULL;  
        westList->westHead = tempNode;
        westList->westTail = tempNode;
    }
    else
    {
        tempNode = malloc(sizeof(WestNode));
        // tempNode->previous = NULL;
        tempNode->westData = toBeAdded;
        tempNode->westTimeData = timeToBeAdded;
        tempNode->next = westList->westHead;
        westList->westHead = tempNode;
    }
}

void deleteWestList(WestList *westList)
{

    WestList * temp;
    temp = westList;

    WestNode * tempNode;
    tempNode = westList->westHead;

    if(westList != NULL)
    {
        while(tempNode->next != NULL)
        {
             tempNode = tempNode->next;
             free(tempNode);
        }
        free(westList);
    } 
}

void insertWestSorted(WestList *westList, void *toBeAdded, void *timeToBeAdded)
{

    WestNode * tempNode = malloc(sizeof(WestNode));
    tempNode = westList->westHead;


    if(tempNode == NULL)
    {
        // printf("node is null\n");

        tempNode = malloc(sizeof(WestNode));
        tempNode->westData = toBeAdded;
        tempNode->westTimeData = timeToBeAdded;
        // printf("init: %s, fin: %s\n", (char *)tempNode->westTimeData, (char *)timeToBeAdded);
        tempNode->next = NULL;  
        westList->westHead = tempNode;
        westList->westTail = tempNode;
    } 
    else if(tempNode->westTimeData <= timeToBeAdded)
    {
        // printWestForward(westList);
        // printf("init: %s, fin: %s\n", (char *)tempNode->westTimeData, (char *)timeToBeAdded);
         tempNode= malloc(sizeof(WestNode));
        while(tempNode->next != NULL)
        {
            tempNode->next->westData = tempNode->westData;
            tempNode->next->westTimeData = tempNode->westTimeData;
            tempNode->next->next = tempNode->next;
            tempNode->westData = toBeAdded;
            tempNode->westTimeData = timeToBeAdded;
            tempNode->next = tempNode;
        }
    }
    else
    {
        while(tempNode->next != NULL || tempNode->next->westTimeData < timeToBeAdded)
        {
            printf("tits\n");
            tempNode = tempNode->next;
            printf("%s\n", (char *)tempNode->next->westTimeData);
        }
        printf("\nttities\n");
        tempNode = malloc(sizeof(WestNode));
        tempNode->westData = toBeAdded;
        tempNode->westTimeData = timeToBeAdded;
        tempNode->next = tempNode;
    }



    // struct node* current;
    // /* Special case for the head end */
    // if (*head_ref == NULL || (*head_ref)->data >= new_node->data)
    // {
    //     new_node->next = *head_ref;
    //     *head_ref = new_node;
    // }
    // else
    // {
    //      Locate the node before the point of insertion 
    //     current = *head_ref;
    //     while (current->next!=NULL &&
    //            current->next->data < new_node->data)
    //     {
    //         current = current->next;
    //     }
    //     new_node->next = current->next;
    //     current->next = new_node;
    // }

}

int deleteDataFromWestList(WestList *westList, void *toBeDeleted)
{

    WestList * temp;
    temp = westList;

    WestNode * tempNode;
    tempNode = westList->westHead;

    while(tempNode->next != NULL)
    {
        if(tempNode->westData == toBeDeleted)
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

    return tempNode->westData;

}

void *getFromWestBack(WestList *westList)
{

    WestList * temp;
    temp = westList;

    WestNode * tempNode;
    tempNode = temp->westTail;


    return tempNode->westData;
}

void printWestForward(WestList *westList)
{

    WestList * temp;
    temp = westList;

    WestNode * tempNode;
    tempNode = westList->westHead;

    while(tempNode != NULL)
    {
        // printf("hiya\n");
        temp->printData(tempNode->westData);
        tempNode = tempNode->next;
        // tempNode->previous = tempNode;
    }
}

void printWestData(WestList *westList)
{

    WestList * temp;
    temp = westList;

    WestNode * tempNode;
    tempNode = westList->westHead;

    // while(tempNode != NULL)
    // {
        temp->printData(tempNode->westData);
        tempNode = tempNode->next;
        // tempNode->previous = tempNode;
    // }
}

void printWestTimeData(WestList *westList)
{

    WestList * temp;
    temp = westList;

    WestNode * tempNode;
    tempNode = westList->westHead;

    // while(tempNode != NULL)
    // {
        temp->printData(tempNode->westTimeData);
        tempNode = tempNode->next;
        // tempNode->previous = tempNode;
    // }
}
