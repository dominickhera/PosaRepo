#include "LinkedListAPI.h"

List *initializeList(void (*printFunction)(void *tobePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first, const void *second))
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
    Node * tempNode;
    tempNode = list->head;
    
    if(tempNode == NULL)
    {
        tempNode = malloc(sizeof(Node));
        tempNode->previous = NULL;
        tempNode->data = toBeAdded;
        tempNode->next = NULL;  
        list->head = tempNode;
        list->tail = tempNode;
    }
    else
    {
        tempNode = malloc(sizeof(Node));
        tempNode->previous = NULL;
        tempNode->data = toBeAdded;
        tempNode->next = list->head;
        list->head = tempNode;
    }
}

void insertBack(List *list, void *toBeAdded)
{
    Node * tempNode = NULL;
    tempNode = (Node*)malloc(sizeof(Node));
    tempNode = list->head;
    if(tempNode!= NULL)
    {
        tempNode = malloc(sizeof(Node));
        tempNode->previous = list->tail;
        tempNode->next = NULL;
        tempNode->data = toBeAdded;
        list->tail = tempNode; 
    }
    else
    {
        tempNode = malloc(sizeof(Node));
        tempNode->previous = NULL;
        tempNode->data = toBeAdded;
        tempNode->next = NULL;
        list->head = tempNode;
        list->tail = tempNode;
    }

}


void deleteList(List *list)
{

    List * temp;
    temp = list;

    Node * tempNode;
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

void insertSorted(List *list, void *toBeAdded)
{
    List * temp;
    temp = list;

    Node * tempNode;
    tempNode = list->head;
    if(tempNode == NULL)
    {
        tempNode = malloc(sizeof(Node));
        tempNode->previous = NULL;
        tempNode->data = toBeAdded;
        tempNode->next = NULL;  
        list->head = tempNode;
        list->tail = tempNode;
    }
    else
    {
        tempNode = malloc(sizeof(Node));
        tempNode->previous = NULL;
        tempNode->data = toBeAdded;
        tempNode->next = list->head;
        list->head = tempNode;
    }

}

int deleteDataFromList(List *list, void *toBeDeleted)
{

    List * temp;
    temp = list;

    Node * tempNode;
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

    Node * tempNode;
    tempNode = temp->head; 

    if(list == NULL)
    {
        printf("error\n");
    }

    return tempNode->data;

}

void *getFromBack(List *list)
{

    List * temp;
    temp = list;

    Node * tempNode;
    tempNode = temp->tail;


    return tempNode->data;
}

void printForward(List *list)
{

    List * temp;
    temp = list;

    Node * tempNode;
    tempNode = list->head;

    while(tempNode != NULL)
    {
        temp->printData(tempNode->data);
        tempNode = tempNode->next;
        tempNode->previous = tempNode;
    }
}

void printBackwards(List *list)
{

    List * temp;
    temp = list;

    Node * tempNode = NULL;
    tempNode = list->tail;

    while(tempNode != NULL)
    {
        temp->printData(tempNode->data);
        tempNode = tempNode->previous;
        tempNode->next = tempNode->previous;
    }

}


