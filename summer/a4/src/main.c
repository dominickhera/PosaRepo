#include "tree.h"
#include "balancedTreeAPI.h"
#include "HashTableAPI.h"
#include "LinkedListAPI.h"

int main(int argc, char ** argv)
{

    FILE * fp;
    FILE * fo;
    char * items[7];
    char line[500];
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
        // int index = 0;
        char * word;

        if(line[strlen(line) - 1] == '\n')
        {
            line[strlen(line) - 1] = '\0';
        }

        word = strtok(line, ",");

        if(titleCheck > 0)
        {
            int index = 0;
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
                    treeInsertNode(tree, items[0],items[1],items[2],items[3],TAXABLE, word, atoi(items[6]));
                }
                else if(strcmp(items[4], "1") == 0)
                {
                    treeInsertNode(tree, items[0],items[1],items[2],items[3],NONTAXABLE, word, atoi(items[6]));
                }

                insertData(hashTable, items[0], items[1]);

            }
        }
        else
        {
            titleCheck++;
        }

    }

    fclose(fp);

    stockCheck(tree->root);
    printf("\n\n");
    while(userChoice != 8)
    {
        printf("1.search for product\n2.add item to customer invoice using product number to identify the item, adjust the inventory as neccessary, user may purchase multiples\n3. remove product from inventory(removes all copies)\n4. print report to screen that gives quantity, alphabettically by product name with one item per line of the report\n5.print report of customers invoice, show taxable items in a seperate list from non taxable items\n6.edit invoice\n7.import addition inventory file.\n8.exit\n\n:/> ");
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

                        insertFront(customerInvoice, tempNode->proID, tempNode->prodName, tempNode->publisher, tempNode->genre, tempNode->taxType, tempNode->price, amountCheck);

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
                printf("\n\n");
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

                            insertFront(customerInvoice, tempNode->proID, tempNode->prodName, tempNode->publisher, tempNode->genre, tempNode->taxType, tempNode->price, amountCheck);
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

                printf("\n\n");
                break;
            case 3:
                printf("\n\nenter name of product you're removing from inventory: ");
                fgets(tempString, 100, stdin);

                if(tempString[strlen(tempString) - 1] == '\n')
                {
                    tempString[strlen(tempString) - 1] = '\0';
                }
                treeDeleteNode(tree, tempString);
                printf("%s has successfully been deleted from inventory\n\n", tempString);
                break;
            case 4:
                printf("\n\n");
                stockCheck(tree->root);
                printf("\n\n");
                break;
            case 5:
                printf("\n\n");
                printInvoice(customerInvoice);
                printf("\n\n");
                break;
            case 6:
                printf("\n\n");
                printForward(customerInvoice);
                printf("\n\nenter name of product to edit/delete: ");
                fgets(tempString, 100, stdin);

                if(tempString[strlen(tempString) - 1] == '\n')
                {
                    tempString[strlen(tempString) - 1] = '\0';
                }

                CustomerNode * tempCustomerNode = findItem(customerInvoice, tempString);
                TreeNode * tempPutBackNode = treeFindNode(tree, tempString);

                if(tempCustomerNode != NULL)
                {
                    int editInt = 0;
                    int addDeleteChoice = 0;
                    while(editInt != 1 || editInt != 2 || editInt != 3)
                    {
                        printf("do you want to delete %s or edit the amount of copies (%d in Invoice)?\n (edit 1/ delete 2/ return to main menu 3): ", (char *)tempCustomerNode->prodName, tempNode->quantity);
                        scanf("%d", &editInt);
                        if(editInt == 1|| editInt == 2 || editInt == 3)
                        {
                            break;
                        }
                        printf("please enter a number between 1 - 3\n");
                    }

                    if(editInt == 1)
                    {

                        amountCheck = tempCustomerNode->quantity + 1;

                        if(tempPutBackNode == NULL)
                        {
                            while(amountCheck > tempCustomerNode->quantity)
                            {
                                printf("How many would you like to remove from your invoice? (Amount in Invoice: %d)/(Amount in Stock: 0): ", tempCustomerNode->quantity);
                                scanf("%d", &amountCheck);

                                if(amountCheck < tempCustomerNode->quantity)
                                {
                                    break;
                                }
                                printf("There are only %d copies in invoice, you can't remove that many.\n", tempCustomerNode->quantity);
                            }

                            if(amountCheck == tempCustomerNode->quantity)
                            {
                                treeInsertNode(tree, tempCustomerNode->proID, tempCustomerNode->prodName, tempCustomerNode->publisher, tempCustomerNode->genre, tempCustomerNode->taxType, tempCustomerNode->price, tempCustomerNode->quantity);
                                deleteDataFromList(customerInvoice, tempString);
                            }
                            else
                            {
                                tempCustomerNode->quantity -= amountCheck;
                                treeInsertNode(tree, tempCustomerNode->proID, tempCustomerNode->prodName, tempCustomerNode->publisher, tempCustomerNode->genre, tempCustomerNode->taxType, tempCustomerNode->price, amountCheck);
                            }

                        }
                        else
                        {
                            while(addDeleteChoice != 1 || addDeleteChoice != 2)
                            {
                                printf("Would you like to add(1) or remove(2) copies of %s?: ", (char *)tempCustomerNode->prodName);
                                scanf("%d", &addDeleteChoice);
                                if(addDeleteChoice == 1 || addDeleteChoice ==2)
                                {
                                    break;
                                }
                                printf("you can only add(1) or remove(2) copies of %s\n", (char *)tempCustomerNode->prodName);

                            }

                            if(addDeleteChoice == 1)
                            {
                                while(amountCheck >= tempPutBackNode->quantity)
                                {

                                    printf("how many copies would you like to add? (Amount in Invoice: %d)/(Amount in Stock: %d) : ", tempCustomerNode->quantity, tempPutBackNode->quantity);
                                    scanf("%d", &amountCheck);


                                    if(amountCheck <= tempPutBackNode->quantity)
                                    {
                                        break;
                                    }
                                    printf("There are only %d copies in stock, you can't add that many.\n", tempPutBackNode->quantity);
                                }

                                if(amountCheck == tempPutBackNode->quantity)
                                {
                                    tempCustomerNode->quantity += tempPutBackNode->quantity;
                                    treeDeleteNode(tree, tempString);
                                }
                                else
                                {
                                    tempCustomerNode->quantity += amountCheck;
                                    tempPutBackNode->quantity -= amountCheck;
                                }
                            }
                            else if(addDeleteChoice == 2)
                            {

                                while(amountCheck > tempCustomerNode->quantity)
                                {

                                    printf("how many copies would you like to remove? (Amount in Invoice: %d)/(Amount in Stock: %d) : ", tempCustomerNode->quantity, tempPutBackNode->quantity);
                                    scanf("%d", &amountCheck);


                                    if(amountCheck <= tempCustomerNode->quantity)
                                    {
                                        break;
                                    }
                                    printf("There are only %d copies in invoice, you can't remove that many.\n", tempCustomerNode->quantity);
                                }


                                if(amountCheck == tempCustomerNode->quantity)
                                {
                                    tempPutBackNode->quantity += tempCustomerNode->quantity;
                                    deleteDataFromList(customerInvoice, tempString);
                                }
                                else
                                {

                                    tempPutBackNode->quantity = tempPutBackNode->quantity + amountCheck;
                                    tempCustomerNode->quantity = tempCustomerNode->quantity - amountCheck;
                                }

                            }
                            addDeleteChoice = 0;
                            amountCheck = 0;
                        }
                    }
                    else if(editInt == 2)
                    {

                        if(tempPutBackNode != NULL)
                        {
                            tempPutBackNode->quantity += tempCustomerNode->quantity;
                        }
                        else
                        {
                            treeInsertNode(tree, tempCustomerNode->proID, tempCustomerNode->prodName, tempCustomerNode->publisher, tempCustomerNode->genre, tempCustomerNode->taxType, tempCustomerNode->price, tempCustomerNode->quantity);
                        }

                        deleteDataFromList(customerInvoice, tempString);
                    }
                    else if(editInt == 3)
                    {
                        // printf("3hole\n");
                        break;
                    }
                }
                else
                {
                    printf("%s does not exist in your invoice....", tempString);
                }
                printf("\n\n");
                break;
            case 7:
                printf("enter name of additional inventory file: ");
                fgets(tempString, 100, stdin);

                if(tempString[strlen(tempString) - 1] == '\n')
                {
                    tempString[strlen(tempString) - 1] = '\0';
                }

                fo = fopen(tempString, "r");

                if(fo == NULL)
                {
                    printf("could not find file\n");
                    break;
                }

                while(fgets(line, sizeof(line), fo) != NULL)
                {
                    char * word;

                    if(line[strlen(line) - 1] == '\n')
                    {
                        line[strlen(line) - 1] = '\0';
                    }

                    word = strtok(line, ",");

                    if(titleCheck > 0)
                    {
                        int index = 0;
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
                                treeInsertNode(tree, items[0],items[1],items[2],items[3],TAXABLE, word, atoi(items[6]));
                            }
                            else if(strcmp(items[4], "1") == 0)
                            {
                                treeInsertNode(tree, items[0],items[1],items[2],items[3],NONTAXABLE, word, atoi(items[6]));
                            }

                            insertData(hashTable, items[0], items[1]);

                        }
                    }
                    else
                    {
                        titleCheck++;
                    }
                }
                fclose(fo);
                printf("%s has successfully been imported.\n\n", tempString);
                break;
            case 8:
                destroyTable(hashTable);
                destroyBalancedBinTree(tree);
                deleteList(customerInvoice);
                printf("bye!\n\n");
                userChoice = 8;
                exit(1);
                break;
            default:
                printf("enter a number between 1-8\n");
                break;
        }
    }

    return 0;
}
