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

CustomerNode *initializeNode(void *data, int quantity, TAX_TYPE taxType, void *price)
{

    CustomerNode * temp = malloc(sizeof(CustomerNode));
    temp->data = malloc(sizeof(data)*100);
    temp->price = malloc(sizeof(price) * 100);

    if(temp == NULL)
    {
        return NULL;
    }

    temp->next = NULL;
    temp->previous = NULL;
    // temp->data = data;
    strcpy(temp->data, data);
    strcpy(temp->price, price);
    temp->quantity = quantity;
    temp->taxType = taxType;
    // temp->taxType = taxType;

    return temp;

}

void insertFront(List *list, void *toBeAdded, int quantity, TAX_TYPE taxType, void *price)
{
    CustomerNode * tempNode = NULL;
    CustomerNode * duplicateNode = list->head;
    int duplicateFlag = 0;

    if(list->head == NULL)
    {
        tempNode = initializeNode(toBeAdded, quantity, taxType, price);
        list->head = tempNode;
    }
    else
    {
        while(duplicateNode != NULL)
        {
            if(strcmp(duplicateNode->data, toBeAdded) == 0)
            {
                duplicateNode->quantity = duplicateNode->quantity + quantity;
                duplicateFlag++;
            }
            duplicateNode = duplicateNode->next;   
        }

        if(duplicateFlag == 0)
        {
            tempNode = initializeNode(toBeAdded, quantity, taxType, price);
            tempNode->next = list->head;
            list->head = tempNode;
        }
    }

    // printf("Title: %s, quantity: %d, taxType: %u\n", (char *)tempNode->data, tempNode->quantity, (unsigned)tempNode->taxType);
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

    // while(tempNode->next != NULL)
    // {
    //     if(tempNode->data == toBeDeleted)
    //     {
    //         if(tempNode->next != NULL)
    //         {
    //             tempNode->next->previous = tempNode->previous;
    //         } 

    //         if(tempNode->previous != NULL)
    //         {
    //             tempNode->previous->next = tempNode->next;
    //         }
    //         free(tempNode);
    //     }
    //     tempNode = tempNode->next;
    // }

    while(strcmp(tempNode->data, toBeDeleted) != 0)
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

    if(tempNode == temp->head)
    {
        temp->head = tempNode->next;
    }
    else
    {
        tempNode->previous->next = tempNode->next;
    }

    if(tempNode == temp->tail)
    {
        temp->tail = tempNode->previous;
    }
    else
    {
        tempNode->next->previous = tempNode->previous;
    }

    free(tempNode->data);
    free(&tempNode->quantity);
    free(&tempNode->taxType);
    free(&tempNode->price);
    free(tempNode);

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

    // List * temp;
    // temp = list;

    CustomerNode * tempNode;
    tempNode = list->head;
    float totalNonTax;
    float totalTax;
    float totalFinal;

    printf("Customer Invoice\n=================\n\nTaxable Items\n=============\n");

    while(tempNode != NULL)
    {
        if(tempNode->taxType == 0)
        {
            printf("%s, Quantity: %d\n", tempNode->data, tempNode->quantity);
        }
        // temp->printData(tempNode->data);
        tempNode = tempNode->next;
        // tempNode->previous = tempNode;
    }

    tempNode = list->head;

    printf("\n\nNon-Taxable Items\n================\n");

    while(tempNode != NULL)
    {
        if(tempNode->taxType == 1)
        {
            printf("%s, Quantity: %d\n", tempNode->data, tempNode->quantity);
        }
        // temp->printData(tempNode->data);
        tempNode = tempNode->next;
        // tempNode->previous = tempNode;
    }


}


