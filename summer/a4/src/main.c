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

    fp = fopen(argv[1], "r");

    if(fp == NULL)
    {
        printf("could not find file\n");
        return 0;
    }

    Tree *tree = createBalancedBinTree(compareFunction, &free, &copyFunction);
    HTable * hashTable = createHashTable(50000, &hashData, &free, &printData);
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

            // insertData(hashTable, items[0], items[1]);

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
        printf("1.search for product\n2.add item to customer invoice using product number to identify the item, adjust the inventory as neccessary, user may purchase multiples\n3. remove product from inventory(removes all copies)\n4. print report to screen that gives quantity, alphabettically by product name with one item per line of the report\n5.print report of customers invoice, show taxable items in a seperate list from non taxable items\n6.inorder print\n7.exit\n");
        scanf("%d", &userChoice);
        char tempString[256];
        getchar();
        switch(userChoice)
        {
            case 1:
                printf("enter name of product you're searching for: ");
                fgets(tempString, 100, stdin);

                if(tempString[strlen(tempString) - 1] == '\n')
                {
                    tempString[strlen(tempString) - 1] = '\0';
                } 

                TreeNode * tempNode = treeFindNode(tree, tempString);
                if(tempNode != NULL)
                {
                    printf("\n\nFound: %s,Product ID: %s, Publisher: %s, Price: $%s, Genre: %s, Amount in Stock: %d\n", (char *)tempNode->prodName, (char *)tempNode->proID, (char *)tempNode->publisher, (char *)tempNode->price, (char *)tempNode->genre, tempNode->quantity);


                }
                else
                {
                    printf("could not find %s in our system...\n", tempString);
                }
                break;
            case 2:
                printf("enter name of product you're searching for: ");
                fgets(tempString, 100, stdin);

                if(tempString[strlen(tempString) - 1] == '\n')
                {
                    tempString[strlen(tempString) - 1] = '\0';
                } 

                if(lookupData(hashTable, tempString) != NULL)
                {
                    TreeNode * tempNode = treeFindNode(tree, (char *)lookupData(hashTable, tempString));

                    if(tempNode != NULL)
                    {
                       printf("\nFound: %s, Publisher: %s, Price: $%s, Genre: %s, Amount in Stock: %d\n", (char *)tempNode->prodName, (char *)tempNode->publisher, (char *)tempNode->price, (char *)tempNode->genre, tempNode->quantity);

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
                break;
            case 4:
                stockCheck(tree->root);
                printf("\n");
                break;
            case 5:
                break;
            case 6:
                treeInOrderPrint(tree, &printData);
                break;
            case 7:
                // printf("7\n");
                userChoice = 7;
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
