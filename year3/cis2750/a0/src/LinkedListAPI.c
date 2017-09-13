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

	if(list != NULL)
    {
         free(list);
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
	// printf("create shit\n");

	printf("1\n");
	List temp = list;
	printf("1\n");
	ListIterator * tempIter = malloc(sizeof(ListIterator));

	printf("1\n");
	tempIter->current = temp.head;

	printf("1\n");
	return *tempIter;
	
}

void* nextElement(ListIterator* iter)
{
	// printf("hi\n");

	printf("a\n");
	ListIterator tempIter = *iter;
	printf("b\n");
	tempIter.current->previous = tempIter.current;
	printf("c\n");
	tempIter.current = tempIter.current->next;
	printf("d\n");

	return tempIter.current;


}
