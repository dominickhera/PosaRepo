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

    Node * temp; 
    Node * currentPosition;

    currentPosition = list->head;

    while(currentPosition->next != NULL)
    {
        temp = currentPosition->next;
        list->deleteData(currentPosition->data);
        free(currentPosition);
        currentPosition = temp;
    }

}

void insertSorted(List *list, void *toBeAdded)
{

    if(list != NULL)
    {
        toBeAdded = list->tail;
        // return toBeAdded;
    }
    else
    {
        return;
    }

}

int deleteDataFromList(List *list, void *toBeDeleted)
{

    List * temp;
    temp = list;

    Node * tempNode;
    tempNode = list->head;

    /*while(tempNode->next != NULL)
    {
        if(tempNode->data == toBeDeleted)
        {
            // toBeDeleted = tempNode->data;
            // free(tempNode->data);
            temp->deleteData(tempNode->data);
            free(tempNode->data);
            return;
            // return toBeDeleted;
        }
        tempNode->previous = tempNode;
        tempNode = tempNode->next;
    }
*/
    while(tempNode->data != toBeDeleted)
    {
        if(tempNode->next == NULL)
        {
            return 0;
        } 
        else
        {
            tempNode->previous = tempNode;
            tempNode = tempNode->next; 
        }
    }

    return 0;
    // free(tempNode->data);

    // return temp;

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

    // if(list == NULL)
    // {
    //     return;
    // }

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

    // if(list == NULL)
    // {
    //     return;
    // }

    while(tempNode != NULL)
    {
        temp->printData(tempNode->data);
        tempNode = tempNode->previous;
        tempNode->next = tempNode->previous;
    }

}


