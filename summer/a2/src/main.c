#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"
#include "HashTableAPI.h"

int main()
{
    // printf("hi\n");

    int userInput = 0;
    int passwordVaultSize = 0;
    char fileName[256];
    char line[256];
    char tempPass[256];
    char tempKey[256];
    char tempStr[256];
    FILE *fp;

    HTable * hashTable = createTable(500, &hashData, &free, &printData);

    while(userInput != 7)
    {
        printf("1: Open Password File\n2: Add New Password\n3: Remove Password\n4: Retrieve a Password\n5: Update a Password\n6: Print List of Passwords\n7: Exit\n\n> ");
        scanf("%d", &userInput);
        switch(userInput)
        {
            case 1:
                printf("enter file name: ");
                scanf("%s", fileName);
                fp = fopen(fileName, "r");
                if(fp == NULL)
                {
                    printf("could not find file\n\n");
                    break;
                }

                while(fgets(line, sizeof(line), fp) != NULL)
                {
                    printf("%s\n", line);
                }

                break;
            case 2:
                // printf("1: %s\n", tempStr);
                memset(tempPass, 0, 256);
                memset(tempKey, 0, 256);
                // printf("2: %s\n", tempStr);
                printf("what program/site is this for? : ");
                scanf("%s", tempKey);
                printf("enter new password into vault: ");
                scanf("%s", tempPass);
                // printf("3: %s\n", tempStr);
                insertData(hashTable, tempKey, tempPass);
                passwordVaultSize++;
                // memset(tempStr, 0, sizeof(tempStr));
                break;
            case 3:
                printf("remove\n");
                break;
            case 4:
                memset(tempStr, 0, 256);
                printf("what program/website is this password for? : ");
                scanf("%s", tempStr);
                if(lookupData(hashTable, tempStr) != NULL)
                {
                printf("\nFound it!\nYour %s Password is %s\n\n", tempStr,(char*)lookupData(hashTable, tempStr));
                }
                else
                {
                    printf("\nSorry, but I couldn't find any password for your %s account...\n", tempStr);
                }
                // printf("Retrieve\n");
                break;
            case 5:
                printf("update\n");
                break;
            case 6:
                // printf("print list\n");
                if(passwordVaultSize != 0)
                {
                    printf("List:\n\n");
                for(int i = 0; i < passwordVaultSize+1; i++)
                {
                    // printf("%d: %s\n", i, (char*)lookupData(hashTable, i));

                }
                printf("\n");
                }
                else
                {
                    printf("there currently are no passwords in your vault.\n\n");
                }
                break;
            case 7:
                return 0;
            default:
                printf("please enter a number between 1-7\n");
        }
    }

    return 0;
}

