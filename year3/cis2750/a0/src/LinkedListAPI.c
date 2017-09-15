/*

 * CIS2750 F2017

 * Assignment 0

 * Dominick Hera 0943778

 * This file contains the implementation of the linked List API

 * This implementation is based on the List API that I implemented in my Assignment 1 for CIS2520, whcih I took

 * in the summer of 2017 with professor Judi McCuaig.  The permission to use my CIS2520 code in CIS2750 was obtained on my behalf by

 * my current CIS2750 professor, Denis Nikitenko.

 */


#include "LinkedListAPI.h"

List initializeList(char* (*printFunction)(void *toBePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first,const void *second))
{

	List * temp = NULL;

    if((temp = (List*)malloc(sizeof(List))) != NULL)
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

    temp->data = malloc(sizeof(data) * 100);
    temp->next = NULL;
    temp->previous = NULL;
    strcpy(temp->data, data);

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

    Node * tempNode = NULL;

    tempNode = list->head;

    if(tempNode != NULL)
    {
        tempNode = initializeNode(toBeAdded);
        tempNode->previous = list->tail;
        list->tail = tempNode; 
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

	List * temp;
    temp = list;

    // Node * tempNode = findItem(list, toBeDeleted);
    Node * tempNode;
    tempNode = list->head;

    if(tempNode == NULL)
    {
        return NULL;
    }

    while(strcmp(tempNode->data, toBeDeleted) != 0)
    {
        if(tempNode->next == NULL)
        {
            return NULL;
        }
        else
        {
            tempNode->previous = tempNode;
            tempNode = tempNode->next;
        }
    }

    if(tempNode != NULL)
    {

        if(tempNode == temp->head)
        { 
            temp->head = tempNode->next;
        }
        
        if(tempNode == temp->tail)
        {
            temp->tail = tempNode->previous;
        }

        tempNode->previous = tempNode->next;
        
        free(tempNode);

    }
    else
    {
        printf("Item does not exist...\n");
    }


    return 0;

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

	List * temp = &list;

    Node * tempNode = temp->head;

    while(tempNode != NULL)
    {
        temp->printData(tempNode->data);
        tempNode = tempNode->next;
        tempNode->previous = tempNode;
    }

    return (char *)tempNode->data;

}

ListIterator createIterator(List list)
{

	List temp = list;
	ListIterator * tempIter = malloc(sizeof(ListIterator)*1000);
	tempIter->current = temp.head;

	return *tempIter;
	
}

void* nextElement(ListIterator* iter)
{
	// printf("hi\n");

	//THIS IS THE FUNCTION THAT IS FUCKING UP//

	printf("a\n");
	ListIterator * tempIter = iter;
	// ListIterator * tempIter = malloc(sizeof(ListIterator)*1000);
	// tempIter = iter;
	printf("b\n");
	// tempIter->current->previous = tempIter->current;
	printf("c\n");
	tempIter->current = tempIter->current->next;
	printf("current: %p\n", (void*)tempIter);
	printf("d\n");

	return tempIter->current;


}