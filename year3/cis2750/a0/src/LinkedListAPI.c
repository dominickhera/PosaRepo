/*

 * CIS2750 F2017

 * Assignment 0

 * Dominick Hera 0943778

 * This file contains the implementation of the linked List API

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
        // return NULL;


        temp->head = NULL;
        temp->tail = NULL;
        temp->printData = printFunction;
        temp->deleteData = deleteFunction;
        temp->compare = compareFunction;

        // return *temp;
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

    // temp->data = malloc(sizeof(data) * 100);
    temp->next = NULL;
    temp->previous = NULL;
    temp->data = data;
    // strcpy(temp->data, data);

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
        // tempNode = initializeNode(toBeAdded);
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


    //THIS IS CAUSING THE MEMORY ALLOCATION ERROR, YOU HAVE TO FIX THIS
    if(list != NULL)
    {

        Node * tempNode = list->head;
        while(tempNode != NULL)
        {

            free(tempNode);
            tempNode = tempNode->next;

        }

        // printf("free SHEET\n");
        // free(list);
    } 
    else
    {
        printf("butts\n");
    }

}

void insertSorted(List* list, void *toBeAdded)
{

    /*FIX LATER PLEASE*/

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

void* deleteDataFromList(List* list, void *toBeDeleted)
{

    List temp = *list;
    Node * tempNode = temp.head;

    void* tempDataThing = toBeDeleted;

    // printf("tbd: %s\n", tempDataThing);

    if(tempNode == NULL)
    {
        return NULL;
    }

    while(tempNode != NULL)
    {
        // if(tempNode->next != NULL)
        // {
        if(temp.compare(tempNode->data, tempDataThing) == 0)
        {
            Node * tempReturnNode = tempNode;
            if(temp.head == tempNode)
            { 
                // printf("h1\n");
                printf("1\n");
                tempReturnNode = temp.head;
                // free(temp.head);
                temp.head = tempNode->next;
                printf("2\n");
                temp.head->previous = NULL;
                // free(tempNode->datasssss\\);
                printf("3\n");
                // tempReturnNode = temp.head;
            }
            
            if(tempNode->next != NULL)
            {
            	printf("4\n");
                tempNode->next->previous = tempNode->previous;
            }
            printf("5\n");
            if(temp.tail == tempNode)
            {
            		printf("6\n");
                // printf("t1\n");
                temp.tail = tempNode->previous;
                printf("7\n");
                temp.tail->next = NULL;
                printf("8\n");
            }
            printf("9\n");
            if(tempNode->previous != NULL)
            {
            	printf("10\n");
                tempNode->previous->next = tempNode->next;
            }
            printf("11\n");
               // list->deleteData(tempNode->data);
            // free(tempNode);

            return tempReturnNode->data;
        	// return tempNode->data;
        }

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

	printf("fuck\n\n");
    List temp = list;
    printf("1\n");
    Node * tempNode = temp.head;
    printf("2\n");
    char * listString = malloc(sizeof(char)*10000);
    char * newListString = malloc(sizeof(char)*10000);
printf("3\n");
    while(tempNode != NULL)
    {
    	printf("4\n");
        newListString = temp.printData(tempNode->data);
        strcat(listString, "\n");
        printf("5\n");
        strcat(listString,newListString);
        printf("6\n");
        // strcat(listString, "\n");
        tempNode = tempNode->next;
        printf("7\n");
        // tempNode->previous = tempNode;
    }
printf("8\n");
    return listString;

}

ListIterator createIterator(List list)
{
    // printf("create iter\n");
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

    // printf("fuuuuk\n");
    return NULL;


}
