/*

 * CIS2750 F2017

 * Assignment 1

 * Dominick Hera 0943778

 * This file contains the implementation of the linked List API that also utilises an iterator to traverse through the doubly linked list.

 * This implementation is based on the List API that I implemented in my Assignment 1 for CIS2520, which I took

 * in the summer of 2017 with professor Judi McCuaig.  The permission to use my CIS2520 code in CIS2750 was obtained on my behalf by

 * my current CIS2750 professor, Denis Nikitenko.

 */


#include "LinkedListAPI.h"

List initializeList(char* (*printFunction)(void *toBePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first,const void *second))
{

    // List * temp = NULL;

    List temp;
    // if((temp = malloc(sizeof(List))) != NULL)
    // {

        temp.head = NULL;
        temp.tail = NULL;
        temp.printData = printFunction;
        temp.deleteData = deleteFunction;
        temp.compare = compareFunction;

    // }

    return temp;
}


Node* initializeNode(void *data)
{

    Node * temp;

    temp = (Node*)malloc(sizeof(Node));
    if (temp == NULL)
    {
        return NULL;
    }

    // temp->data = malloc(sizeof(data));
    // strcpy(temp->data, data);
    // printf("wtf\n");
    temp->data = data;
    temp->previous = NULL;
    temp->next = NULL;

    return temp;

}

void insertFront(List* list, void *toBeAdded)
{
    if(list != NULL)
    {
        Node * tempNode = NULL;

        if(list->head == NULL)
        {
            tempNode = initializeNode(toBeAdded);
            list->head = tempNode;
            list->tail = tempNode;
        }
        else
        {
            tempNode = initializeNode(toBeAdded);
            list->head->previous = tempNode;
            tempNode->next = list->head;
            list->head = tempNode;
        }

    }
}

void insertBack(List* list, void *toBeAdded)
{

    if(list != NULL && toBeAdded != NULL)
    {

        Node* tempNode = initializeNode(toBeAdded);
        if(list->head == NULL && list->tail == NULL)
        {
            // printf("1\n");
            list->head = tempNode;
            list->tail = tempNode;
        }
        else
        {
            // printf("2\n");
            tempNode->previous = list->tail;
            list->tail->next = tempNode;
            list->tail = tempNode;
            // printf("head is %p\n\n", list->head);
        }
        // Node * tempNode = list->head;
        // if(tempNode != NULL)
        // {
        //     while(tempNode->next != NULL)
        //     {
        //         tempNode = tempNode->next;
        //     }

        //     tempNode->next = initializeNode(toBeAdded);
        //     list->tail = tempNode->next;
        //     tempNode->next->previous = tempNode;

        // }
        // else
        // {
        //     tempNode = initializeNode(toBeAdded);
        //     list->head = tempNode;
        //     list->tail = tempNode;
        // }
    }

}

void clearList(List* list)
{

    if(list != NULL)
    {

        Node * tempNode = list->head;
        while(tempNode != NULL)
        {
            // list->deleteData(tempNode->data);
            list->deleteData(tempNode);
            tempNode = tempNode->next;
        }
        list->head = NULL;
        list->tail = NULL;
        free(list);
    } 

}

void insertSorted(List* list, void *toBeAdded)
{

    if(list != NULL)
    {
        Node * tempNode = list->head;
        if(tempNode != NULL)
        {
            Node * newNode = initializeNode(toBeAdded);
            while(tempNode != NULL)
            {
                if(tempNode->next != NULL && list->compare(tempNode->data, newNode->data) < 0)
                {   
                    tempNode->previous = tempNode;
                    tempNode = tempNode->next;
                }
                else
                {
                    break;
                }
            }

            if(list->compare(tempNode->data, newNode->data) < 0)
            {
                tempNode->next = newNode;
                newNode->previous = tempNode;
                newNode->next = tempNode->next->next;
                list->tail = newNode;
            }
            else if(tempNode->previous == NULL)
            {
                list->head->previous = newNode;
                newNode->next = list->head;
                list->head = newNode;
            }
            else
            {
                tempNode->previous->next = newNode;
                newNode->next = tempNode;
                newNode->previous = tempNode->previous;
                tempNode->previous = newNode;                
            }

        }
        else
        {
            tempNode = initializeNode(toBeAdded);
            list->head = tempNode;
            list->tail = tempNode;
        }
    }
}

void* deleteDataFromList(List* list, void *toBeDeleted)
{

    if(list != NULL)
    {
        List temp = *list;
        Node * tempNode = temp.head;

        void* tempDataThing = toBeDeleted;

        if(tempNode == NULL || toBeDeleted == NULL)
        {
            return NULL;
        }

        while(tempNode != NULL)
        {
            if(temp.compare(tempNode->data, tempDataThing) == 0)
            {

                if(tempNode->previous != NULL && tempNode->next != NULL)
                {
                    tempNode->previous->next = tempNode->next;
                    tempNode->next->previous = tempNode->previous;
                }

                Node * tempReturnNode = tempNode;
                if(tempNode->next == NULL)
                {
                    list->tail = tempNode->previous;
                    tempNode->previous->next = NULL;
                }

                if(tempNode->previous == NULL)
                {
                    list->head = tempNode->next;
                    tempNode->next->previous = NULL;
                }

                return tempReturnNode->data;
            }
            tempNode = tempNode->next;
        }
    }

    return NULL;

}

void* getFromFront(List list)
{
    Node* tempB = list.head;
    if(tempB != NULL)
    {
        List * temp = &list;
        Node * tempNode;
        tempNode = temp->head; 
        return tempNode->data;
    }

    return NULL;

}

void* getFromBack(List list)
{

    Node* tempB = list.head;
    if(tempB != NULL)
    {
        List * temp = &list;
        Node * tempNode;
        tempNode = temp->tail;
        return tempNode->data;
    }
    return NULL;

}

char* toString(List list)
{

    List  * temp = &list;

    if(temp != NULL)
    {
        Node * tempNode = temp->head;
        char * listString = malloc(sizeof(char)*100);
        char * newListString = malloc(sizeof(char)*100);

        while(tempNode != NULL)
        {
            newListString = temp->printData(tempNode->data);
            strcat(listString, "\n");
            strcat(listString,newListString);
            tempNode = tempNode->next;
        }
        return listString;
    }
    return NULL;
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
