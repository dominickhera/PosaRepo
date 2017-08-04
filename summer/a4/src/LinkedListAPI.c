#include "LinkedListAPI.h"

List *initializeList(void (*printFunction)(void *tobePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(void *first, void *second))
{
    List * temp = NULL;
    temp = (List*)malloc(sizeof(List));

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

CustomerNode *initializeNode(void *data, int quantity, TAX_TYPE taxType)
{

    CustomerNode * temp = malloc(sizeof(CustomerNode));
    temp->data = malloc(sizeof(temp->data));

    if(temp == NULL)
    {
        return NULL;
    }

    temp->next = NULL;
    temp->previous = NULL;
    // temp->data = data;
    strcpy(temp->data, data);
    temp->quantity = quantity;
    temp->taxType = taxType;

    return temp;

}

void insertFront(List *list, void *toBeAdded, int quantity, TAX_TYPE taxType)
{
    CustomerNode * tempNode = initializeNode(toBeAdded, quantity, taxType);
    tempNode = list->head;
    
    if(tempNode == NULL)
    {
        // tempNode = malloc(sizeof(CustomerNode));
        // tempNode->previous = NULL;
        // tempNode->data = toBeAdded;
        // tempNode->next = NULL;  
        list->head = tempNode;
        list->tail = tempNode;
    }
    else
    {
        // tempNode = malloc(sizeof(CustomerNode));
        // tempNode->previous = NULL;
        // tempNode->data = toBeAdded;
        tempNode->next = list->head;
        list->head = tempNode;
    }
}


void deleteList(List *list)
{

    List * temp;
    temp = list;

    CustomerNode * tempNode;
    tempNode = list->head;

    if(list != NULL)
    {
        while(tempNode->next != NULL)
        {
             tempNode = tempNode->next;
             free(tempNode);
        }
        free(list);
    } 
}


int deleteDataFromList(List *list, void *toBeDeleted, int quantity, TAX_TYPE taxType)
{

    List * temp;
    temp = list;

    CustomerNode * tempNode;
    tempNode = list->head;

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

void *getFromFront(List *list)
{

    List * temp;
    temp = list;

    CustomerNode * tempNode;
    tempNode = temp->head; 

    if(list == NULL)
    {
        printf("error\n");
    }

    return tempNode->data;

}

void printForward(List *list)
{

    List * temp;
    temp = list;

    CustomerNode * tempNode;
    tempNode = list->head;

    while(tempNode != NULL)
    {
        temp->printData(tempNode->data);
        tempNode = tempNode->next;
        tempNode->previous = tempNode;
    }
}


