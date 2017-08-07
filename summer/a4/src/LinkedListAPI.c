#include "LinkedListAPI.h"

List *initializeList(void (*printFunction)(void *tobePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(void *first, void *second))
{
    List * temp = NULL;

    if((temp = (List*)malloc(sizeof(List))) == NULL)
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

CustomerNode *initializeNode(void *proID, void *prodName, void *publisher, void *genre, TAX_TYPE taxType,void *price, int quantity)
{

    CustomerNode * temp = NULL;

    if((temp = malloc(sizeof(CustomerNode))) == NULL)
    {
        return NULL;
    }

    temp->proID = malloc(sizeof(proID) * 100);
    temp->prodName = malloc(sizeof(prodName) * 100);
    temp->publisher = malloc(sizeof(publisher) * 100);
    temp->genre = malloc(sizeof(genre) * 100);
    temp->price = malloc(sizeof(price) * 100);

    temp->next = NULL;
    temp->previous = NULL;
    strcpy(temp->proID, proID);
    strcpy(temp->prodName, prodName);
    strcpy(temp->publisher, publisher);
    strcpy(temp->genre, genre);
    strcpy(temp->price, price);
    temp->quantity = quantity;
    temp->taxType = taxType;

    return temp;

}

void insertFront(List *list, void *proID, void *prodName, void *publisher, void *genre, TAX_TYPE taxType,void *price, int quantity)
{
    CustomerNode * tempNode = NULL;
    CustomerNode * duplicateNode = list->head;

    if(list->head == NULL)
    {
        tempNode = initializeNode(proID, prodName, publisher, genre, taxType, price, quantity);
        list->head = tempNode;
    }
    else
    {
        int duplicateFlag = 0;

        while(duplicateNode != NULL)
        {
            if(strcmp(duplicateNode->prodName, prodName) == 0)
            {
                duplicateNode->quantity = duplicateNode->quantity + quantity;
                duplicateFlag++;
            }
            duplicateNode = duplicateNode->next;   
        }

        if(duplicateFlag == 0)
        {
            tempNode = initializeNode(proID, prodName, publisher, genre, taxType, price, quantity);
            tempNode->next = list->head;
            list->head = tempNode;
        }
    }

    // printf("Title: %s, quantity: %d, taxType: %u\n", (char *)tempNode->data, tempNode->quantity, (unsigned)tempNode->taxType);
}


void deleteList(List *list)
{

    if(list != NULL)
    {
         free(list);
    } 
}


int deleteDataFromList(List *list, void *toBeDeleted)
{

    List * temp;
    temp = list;

    CustomerNode * tempNode = findItem(list, toBeDeleted);

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

void printForward(List *list)
{

    CustomerNode * tempNode;
    tempNode = list->head;

    while(tempNode != NULL)
    {

        printf("%s, Quantity: %d\n", (char *)tempNode->prodName, tempNode->quantity);

        tempNode = tempNode->next;
    }

}


void printInvoice(List *list)
{

    CustomerNode * tempNode;
    tempNode = list->head;
    float totalNonTax = 0.0;
    float totalTax = 0.0;
    float totalFinal = 0.0;

    printf("Customer Invoice\n=================\n\nTaxable Items\n=============\n");

    while(tempNode != NULL)
    {
        if(tempNode->taxType == 0)
        {
            printf("%s, Quantity: %d, Price per: $%s, Total Price: $%.2f\n", (char *)tempNode->prodName, tempNode->quantity, (char *)tempNode->price, (atof(tempNode->price) * tempNode->quantity));
            totalTax += (atof(tempNode->price) * tempNode->quantity);
        }
        tempNode = tempNode->next;
    }

    tempNode = list->head;

    printf("\n\nNon-Taxable Items\n================\n");

    while(tempNode != NULL)
    {
        if(tempNode->taxType == 1)
        {
            printf("%s, Quantity: %d, Price per: $%s, Total Price: $%.2f\n", (char *)tempNode->prodName, tempNode->quantity, (char *)tempNode->price, (atof(tempNode->price) * tempNode->quantity));
            totalNonTax += (atof(tempNode->price) * tempNode->quantity);
        }
        tempNode = tempNode->next;
    }
    printf("\n\nTotal Price of Taxable Games: $%.2f\n", totalTax);
    printf("Total Price of Non-Taxable Games: $%.2f\n\n", totalNonTax);
    totalFinal = totalTax + totalNonTax;

    printf("Total Price of Taxable and Non-Taxable Games: $%.2f\n", totalFinal);


}

void *findItem(List *list, void *toBeFound)
{

    CustomerNode * tempNode;
    tempNode = list->head;
    if(tempNode == NULL)
    {
        // printf("shit doesnt exist\n");
        return NULL;
    }

    while(strcmp(tempNode->prodName, toBeFound) != 0)
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

    return tempNode;

}


