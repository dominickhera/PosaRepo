#include "tree.h"
#include "balancedTreeAPI.h"
#include "HashTableAPI.h"
#include "LinkedListAPI.h"

int main(int argc, char ** argv)
{

    FILE * fp;
    char * items[7];
    char line[500];
    // char tempString[256];
    int titleCheck = 0;
    int userChoice = 0;
    int addToBasketCheck = 0;
    int amountCheck = 0;

    fp = fopen(argv[1], "r");

    if(fp == NULL)
    {
        printf("could not find file\n");
        return 0;
    }

    Tree * tree = createBalancedBinTree(compareFunction, &free, &copyFunction);
    HTable * hashTable = createHashTable(5000, &hashData, &free, &printData);
    List * customerInvoice = initializeList(&printData, &free, &compareFunction);

    while(fgets(line, sizeof(line), fp) != NULL)
    {
        int index = 0;
        char * word;

        if(line[strlen(line) - 1] == '\n')
        {
            line[strlen(line) - 1] = '\0';
        }

        word = strtok(line, ",");

        if(titleCheck > 0)
        {
            items[index++] = word;

            while((word = strtok(NULL, ",")) != NULL)
            {
                items[index++] = word;
            }

            word = strtok(items[5], "$");

            if(items[0] != NULL)
            {
                if(strcmp(items[4], "0") == 0)
                {
                    // printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n\n", items[0], items[1],items[2],items[3],items[4], word, items[6]);
                    treeInsertNode(tree, items[0],items[1],items[2],items[3],TAXABLE, word, atoi(items[6]));
                }
                else if(strcmp(items[4], "1") == 0)
                {
                    // printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n\n", items[0], items[1],items[2],items[3],items[4], word, items[6]);
                    treeInsertNode(tree, items[0],items[1],items[2],items[3],NONTAXABLE, word, atoi(items[6]));
                }

                insertData(hashTable, items[0], items[1]);
                // printf("%s\n%s\n\n\n", items[0], items[1]);

            }
        }
        else
        {
            titleCheck++;
        }

    }

    while(userChoice != 7)
    {
        printf("1.search for product\n2.add item to customer invoice using product number to identify the item, adjust the inventory as neccessary, user may purchase multiples\n3. remove product from inventory(removes all copies)\n4. print report to screen that gives quantity, alphabettically by product name with one item per line of the report\n5.print report of customers invoice, show taxable items in a seperate list from non taxable items\n6.edit invoice\n7.inorder print\n8.exit\n\n");
        scanf("%d", &userChoice);
        char tempString[256];
        getchar();
        switch(userChoice)
        {
            case 1:
                printf("\n\nenter name of product you're searching for: ");
                fgets(tempString, 100, stdin);

                if(tempString[strlen(tempString) - 1] == '\n')
                {
                    tempString[strlen(tempString) - 1] = '\0';
                } 

                TreeNode * tempNode = treeFindNode(tree, tempString);
                if(tempNode != NULL)
                {
                    printf("\n\nFound: %s,Product ID: %s, Publisher: %s, Price: $%s, Genre: %s, Amount in Stock: %d\n\n", (char *)tempNode->prodName, (char *)tempNode->proID, (char *)tempNode->publisher, (char *)tempNode->price, (char *)tempNode->genre, tempNode->quantity);

                    while(addToBasketCheck != 1 || addToBasketCheck != 2)
                    {
                        printf("would you like to add this to your cart? (1) yes, (2) no\n");
                        scanf("%d", &addToBasketCheck);
                        if(addToBasketCheck == 1 || addToBasketCheck == 2)
                        {
                            break;
                        }

                        printf("please enter either 1 or 2\n");
                    }

                    if(addToBasketCheck == 1)
                    {
                        amountCheck = tempNode->quantity + 1;
                        while(amountCheck >= tempNode->quantity)
                        {

                            printf("how many copies would you like to add? (Amount in Stock: %d): ", tempNode->quantity);
                            scanf("%d", &amountCheck);
                            if(amountCheck <= tempNode->quantity)
                            {
                                break;
                            }
                            printf("There are only %d copies in stock, you can't buy that many.\n", tempNode->quantity);

                        }
                        // printf("hi\n");

                        insertFront(customerInvoice, tempNode->prodName, amountCheck, tempNode->taxType, tempNode->price);

                        tempNode->quantity = tempNode->quantity - amountCheck;
                        if(tempNode->quantity <= 0)
                        {
                            treeDeleteNode(tree, tempNode->prodName);
                            removeData(hashTable, tempNode->prodName);
                        }

                        addToBasketCheck = 0;
                    }
                    else if(addToBasketCheck == 2)
                    {
                        addToBasketCheck = 0;
                    }
                    amountCheck = 0;

                }
                else
                {
                    printf("could not find %s in our system...\n", tempString);
                }
                break;
            case 2:
                printf("\n\nenter product ID of product you're adding: ");
                fgets(tempString, 100, stdin);

                if(tempString[strlen(tempString) - 1] == '\n')
                {
                    tempString[strlen(tempString) - 1] = '\0';
                } 

                if(lookupData(hashTable, tempString) != NULL)
                {

                    TreeNode * tempNode = treeFindNode(tree, lookupData(hashTable, tempString));

                    if(tempNode != NULL)
                    {
                        
                        printf("\nFound: %s, Publisher: %s, Price: $%s, Genre: %s, Amount in Stock: %d\n\n", (char *)tempNode->prodName, (char *)tempNode->publisher, (char *)tempNode->price, (char *)tempNode->genre, tempNode->quantity);


                         while(addToBasketCheck != 1 || addToBasketCheck != 2)
                    {
                        printf("would you like to add this to your cart? (1) yes, (2) no\n");
                        scanf("%d", &addToBasketCheck);
                        if(addToBasketCheck == 1 || addToBasketCheck == 2)
                        {
                            break;
                        }

                        printf("please enter either 1 or 2\n");
                    }

                        if(addToBasketCheck == 1)
                        {

                            amountCheck = tempNode->quantity + 1;
                            while(amountCheck >= tempNode->quantity)
                            {
                                printf("how many copies would you like to add? (Amount in Stock: %d): ", tempNode->quantity);
                                scanf("%d", &amountCheck);
                                if(amountCheck <= tempNode->quantity)
                                {
                                    break;
                                }
                                printf("There are only %d copies in stock, you can't buy that many.\n", tempNode->quantity);
                            }
                            insertFront(customerInvoice, tempNode->prodName, tempNode->quantity, tempNode->taxType, tempNode->price);
                            tempNode->quantity = tempNode->quantity - amountCheck;
                            if(tempNode->quantity <= 0)
                            {
                                treeDeleteNode(tree, tempNode->prodName);
                                removeData(hashTable, tempNode->prodName);
                            }

                            addToBasketCheck = 0;
                        }
                        else if(addToBasketCheck == 2)
                        {
                            addToBasketCheck = 0;
                        }
                        amountCheck = 0;
                        printf("\n\n");
                    }
                    else
                    {
                        printf("could not find %s in our system...\n", tempString);
                    }
                }
                else
                {
                    printf("could not find %s in our system...\n", tempString);
                }

                // 
                break;
            case 3:
                printf("\n\nenter name of product you're removing from inventory: ");
                fgets(tempString, 100, stdin);

                if(tempString[strlen(tempString) - 1] == '\n')
                {
                    tempString[strlen(tempString) - 1] = '\0';
                }
                treeDeleteNode(tree, tempString);
                break;
            case 4:
                printf("\n\n");
                stockCheck(tree->root);
                printf("\n");
                break;
            case 5:
                printf("\n\n");
                printForward(customerInvoice);
                printf("\n\n");
                break;
            case 6:
                printf("\n\n");
                break;
            case 7:
                printf("\n\n");
                treeInOrderPrint(tree, &printData);
            case 8:
                // printf("7\n");
                userChoice = 8;
                exit(1);
                break;
            default:
                printf("enter a number between 1-7\n");
                break;
        }
    }

    // printf("\n\n");
    // treePreOrderPrint(tree, &printData);
    // printf("\n");
    // treeInOrderPrint(tree, &printData);
    // printf("\n");
    // treePostOrderPrint(tree, &printData);
    // printf("\n\n");
    // destroyBalancedBinTree(tree);

    return 0;
}
