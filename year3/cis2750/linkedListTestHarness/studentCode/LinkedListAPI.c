/*

 * CIS2750 F2017

 * Assignment 0

 * Dominick Hera 0943778

 * This file contains the implementation of the linked List API that also utilises an iterator to traverse through the doubly linked list.

 * This implementation is based on the List API that I implemented in my Assignment 1 for CIS2520, which I took

 * in the summer of 2017 with professor Judi McCuaig.  The permission to use my CIS2520 code in CIS2750 was obtained on my behalf by

 * my current CIS2750 professor, Denis Nikitenko.

 */


#include "LinkedListAPI.h"

List initializeList(char* (*printFunction)(void *toBePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first,const void *second))
{

    List * temp = NULL;

    if((temp = malloc(sizeof(List))) != NULL)
    {

        temp->head = NULL;
        temp->tail = NULL;
        temp->printData = printFunction;
        temp->deleteData = deleteFunction;
        temp->compare = compareFunction;

    }

    return *temp;
}


Node* initializeNode(void *data)
{

    Node * temp = NULL;

    if((temp = malloc(sizeof(Node))) == NULL)
    {
        return NULL;
    }

    temp->next = NULL;
    temp->previous = NULL;
    temp->data = data;

    return temp;

}

void insertFront(List* list, void *toBeAdded)
{

    Node * tempNode = NULL;

    if(list->head == NULL)
    {
        tempNode = initializeNode(toBeAdded);
        list->head = tempNode;
    }
    else
    {
        tempNode = initializeNode(toBeAdded);
        tempNode->next = list->head;

        list->head = tempNode;
    }

}

void insertBack(List* list, void *toBeAdded)
{

    Node * tempNode = list->head;

    if(tempNode != NULL)
    {
        while(tempNode->next != NULL)
        {
            tempNode = tempNode->next;
        }

        tempNode->next = initializeNode(toBeAdded);
        list->tail = tempNode->next;
        tempNode->next->previous = tempNode;

    }
    else
    {
        tempNode = initializeNode(toBeAdded);
        list->head = tempNode;
        list->tail = tempNode;
    }

}

void clearList(List* list)
{

    if(list != NULL)
    {

        Node * tempNode = list->head;
        while(tempNode != NULL)
        {

            free(tempNode);
            tempNode = tempNode->next;

        }
    } 
    else
    {
        printf("butts\n");
    }

}

void insertSorted(List* list, void *toBeAdded)
{
 
 Node * tempNode = list->head;

    if(tempNode != NULL)
    {
        while(tempNode->next != NULL && list->compare(tempNode->data, toBeAdded) < 0)
        {
            tempNode = tempNode->next;
        }

        tempNode->next = initializeNode(toBeAdded);
        list->tail = tempNode->next;
        tempNode->next->previous = tempNode;

    }
    else
    {
        tempNode = initializeNode(toBeAdded);
        list->head = tempNode;
        list->tail = tempNode;
    }

}

void* deleteDataFromList(List* list, void *toBeDeleted)
{

    List temp = *list;
    Node * tempNode = temp.head;

    void* tempDataThing = toBeDeleted;

    if(tempNode == NULL)
    {
        return NULL;
    }

    while(tempNode != NULL)
    {
        if(temp.compare(tempNode->data, tempDataThing) == 0)
        {
            Node * tempReturnNode = tempNode;
            if(temp.head == tempNode)
            { 
                printf("1\n");
                tempNode->next = temp.head;
                printf("2\n");
                // temp.head = tempNode->next;
                // temp.head->previous = NULL;
            }
            printf("3\n");
            if(tempNode->next != NULL)
            {
                printf("4\n");
                tempNode->next->previous = tempNode->previous;
            }
            printf("5\n");

            if(temp.tail == tempNode)
            {
                printf("6\n");
                temp.tail = tempNode->previous;
                printf("7\n");
                temp.tail->next = NULL;
            }
            printf("8\n");
            if(tempNode->previous != NULL)
            {
                printf("9\n");
                tempNode->previous->next = tempNode->next;
            }
            printf("10\n");
            return tempReturnNode->data;
            // printf("11\n");
        }
// printf("12\n");
        tempNode = tempNode->next;

    }

    return NULL;

}

void* getFromFront(List list)
{

    List * temp = &list;

    Node * tempNode;
    tempNode = temp->head; 
    if(temp == NULL)
    {
        printf("error\n");
    }

    return tempNode->data;

}

void* getFromBack(List list)
{

    List * temp = &list;

    Node * tempNode;
    tempNode = temp->tail;

    if(temp == NULL)
    {
        printf("error\n");
    }

    return tempNode->data;

}

char* toString(List list)
{

    printf("25\n");
    List  * temp = &list;
    printf("26\n");
    Node * tempNode = temp->head;
    printf("27\n");
    char * listString = malloc(sizeof(char)*100);
    printf("28\n");
    char * newListString = malloc(sizeof(char)*100);
    printf("29\n");

    while(tempNode != NULL)
    {
        printf("30\n");
        newListString = temp->printData(tempNode->data);
        printf("31\n");
        strcat(listString, "\n");
        printf("32\n");
        strcat(listString,newListString);
        printf("33\n");
        tempNode = tempNode->next;
        printf("34\n");
    }
    printf("35\n");
    return listString;
}

ListIterator createIterator(List list)
{
    List temp = list;
    ListIterator * tempIter = malloc(sizeof(ListIterator)*100);
    tempIter->current = temp.head;

    return *tempIter;
}

void* nextElement(ListIterator* iter)
{

    if(iter->current != NULL)
    {	
        void * tempIter = iter->current->data;

        iter->current = iter->current->next;
        return tempIter;
    }

    return NULL;

}
