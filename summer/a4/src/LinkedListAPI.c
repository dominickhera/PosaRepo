#include "LinkedListAPI.h"

List *initializeList(void (*printFunction)(void *tobePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(void *first, void *second))
{
    List * temp = (List*)malloc(sizeof(List));

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

CustomerNode *initializeNode(void *proID, void *prodName, void *publisher, void *genre, TAX_TYPE taxType,void *price, int quantity)
{

    CustomerNode * temp = malloc(sizeof(CustomerNode));
    temp->proID = malloc(sizeof(proID) * 100);
    temp->prodName = malloc(sizeof(prodName) * 100);
    temp->publisher = malloc(sizeof(publisher) * 100);
    temp->genre = malloc(sizeof(genre) * 100);
    temp->price = malloc(sizeof(price) * 100);


    if(temp == NULL)
    {
        return NULL;
    }
    temp->next = NULL;
    temp->previous = NULL;
    strcpy(temp->proID, proID);
    strcpy(temp->prodName, prodName);
    strcpy(temp->publisher, publisher);
    strcpy(temp->genre, genre);
    strcpy(temp->price, price);
    temp->quantity = quantity;
    temp->taxType = taxType;
    // temp->left = NULL;
    // temp->right = NULL;

    return temp;

}

void insertFront(List *list, void *proID, void *prodName, void *publisher, void *genre, TAX_TYPE taxType,void *price, int quantity)
{
    CustomerNode * tempNode = NULL;
    CustomerNode * duplicateNode = list->head;
    // int duplicateFlag = 0;

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


int deleteDataFromList(List *list, void *toBeDeleted)
{

    List * temp;
    temp = list;

    // printf("1\n");
    CustomerNode * tempNode = findItem(list, toBeDeleted);
    // printf("2\n");
    if(tempNode != NULL)
    {
        // printf("3\n");
        if(tempNode == temp->head)
        { 
           // printf("4\n");
            temp->head = tempNode->next;
        }
            // printf("5\n");
        // else
        // {
            // tempNode = tempNode->next;
        // }

        if(tempNode == temp->tail)
        {
            // printf("6\n");
            temp->tail = tempNode->previous;
        }

        tempNode->previous = tempNode->next;
        
        // printf("18\n");
        free(tempNode);
        // printf("19\n");
        // else
        // {
            // tempNode = tempNode->previous;
        // }

    }
    else
    {
        printf("Item does not exist...\n");
    }
    // while(tempNode->next != NULL)
    // {
    //     if(tempNode->prodName == toBeDeleted)
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



    // while(strcmp(tempNode->prodName, toBeDeleted) != 0)
    // {
    //     if(tempNode->next == NULL)
    //     {
    //         return 0;
    //     }
    //     else
    //     {
    //         tempNode->previous = tempNode;
    //         tempNode = tempNode->next;
    //     }
    // }

    // if(tempNode == temp->head)
    // {
    //     temp->head = tempNode->next;
    // }
    // else
    // {
    //     tempNode->previous->next = tempNode->next;
    // }

    // if(tempNode == temp->tail)
    // {
    //     temp->tail = tempNode->previous;
    // }
    // else
    // {
    //     tempNode->next->previous = tempNode->previous;
    // }

    // free(tempNode->prodName);
    // free(temp)
    // free(&tempNode->quantity);
    // free(&tempNode->taxType);
    // free(&tempNode->price);
    // free(tempNode);

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

    return tempNode->prodName;

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


