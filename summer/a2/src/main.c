#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"
#include "HashTableAPI.h"

int main()
{

    int userInput = 0;
    int passwordVaultSize = 0;
    char fileName[256];
    char line[256];
    char tempPass[256];
    char tempKey[256];
    char tempStr[256];
    FILE *fp;
    // FILE *fo;

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
                memset(tempPass, 0, 256);
                memset(tempKey, 0, 256);
                printf("what program/site is this for? : ");
                scanf("%s", tempKey);
                if(lookupData(hashTable, tempKey) == NULL)
                {
                    printf("enter new password into vault: ");
                    scanf("%s", tempPass);

                    insertData(hashTable, tempKey, tempPass);
                    passwordVaultSize++;
                }
                else
                {
                    printf("\n\nYou already have a password entered for %s, try removing it or updating it instead\n\n", tempKey);
                }
                break;
            case 3:
                memset(tempPass, 0, 256);
                memset(tempKey, 0, 256);
                printf("what is the site/program you want to delete your info for? : ");
                scanf("%s", tempKey);
                removeData(hashTable, tempKey);
                break;
            case 4:
                memset(tempStr, 0, 256);
                printf("what program/website is this password for? : ");
                scanf("%s", tempStr);

                // if(lookupData(hashTable, tempStr) != NULL)
                // {
                    printf("\nFound it!\nYour %s Password is %s\n\n", tempStr,(char*)lookupData(hashTable, tempStr));
                // }
                // else
                // {
                    // printf("\nSorry, but I couldn't find any password for your %s account...\n\n", tempStr);
                // }
                break;
            case 5:
                memset(tempPass, 0, 256);
                memset(tempKey, 0, 256);
                printf("what program/site account info do you wanto to update? : ");
                scanf("%s", tempKey);

                if(lookupData(hashTable, tempKey) != NULL)
                {

                    printf("enter updated password into vault: ");
                    scanf("%s", tempPass);
                    insertData(hashTable, tempKey, tempPass);

                }
                else
                {
                    printf("\n\nYou haven't entered a password for %s yet, try adding one instead\n\n", tempKey);
                }
                break;
            case 6:
                printf("print list\n");
                for(int i = 0; i < hashTable->size;i++)
                {
                    printf("key[%d], data[%s]\n", i, (char*)lookupData(hashTable, "facebook"));
                }
                break;
            case 7:
                destroyTable(hashTable);
                return 0;
            default:
                printf("please enter a number between 1-7\n");
        }
    }

    return 0;
}

