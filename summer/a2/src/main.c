#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"
#include "HashTableAPI.h"

#define character "X"
#define wall '=';

int main()
{

    int c;
    int maxX;
    int maxY;
    int y;
    int x;
    int prevX;
    int prevY;
    int passwordVaultSize = 0;
    int configCount = 0;
    int passCount = 3;
    char line[256];
    char tempPass[256];
    char tempKey[256];
    char tempStr[256];
    char assetLocation[50];
    char fileName[256];
    char outputData[256];
    char masterPassword[256];
    char passwordCheck[256];
    char * parse;
    FILE *fp;
    FILE *config;


    y = 0;
    x = 0;


    char * menuOptions[] = {"Add New Password", "Remove Password", "Retrieve a Password", "Update a Password", "Exit"}; 
    int tempMenuNumb[7];

    HTable * hashTable = createTable(5000, &hashData, &free, &printData);

    strcpy(assetLocation, "./assets/");
    config = fopen("./assets/congfig.txt", "r");

    if(config == NULL)
    {
        config = fopen("./assets/congfig.txt", "w");
        printf("new user detected\n\nenter new master password: ");
        scanf("%s", masterPassword);
        fprintf(config, "%s\n", masterPassword);
        printf("enter name of your new password storage file: ");
        scanf("%s", tempKey);
        strcat(fileName, assetLocation);
        strcat(fileName, tempKey);
        fp = fopen(fileName, "w");
        fprintf(config, "%s", fileName);
        fclose(config);
    }
    else
    {

        while(fgets(line, sizeof(line), config) != NULL)
        {
            if(configCount == 0)
            {
                strcpy(masterPassword, line);
                configCount++;
            }
            else if(configCount == 1)
            {
                strcpy(fileName, line);
                configCount++;
            }

        }

        fp = fopen(fileName, "r");

        while(fgets(line, sizeof(line), fp) != NULL)
        {

            if(line[strlen(line) - 1] == '\n')
            {
                line[strlen(line) - 1] = '\0';
            }

            parse = strtok(line, ",");
            strcpy(tempKey, parse);

            while((parse = strtok(NULL, ",")) != NULL)
            {

                strcpy(tempPass, parse);

            }

            insertData(hashTable, tempKey, tempPass);
            passwordVaultSize++;

        }
    }


    initscr();
    // noecho();
    getmaxyx(stdscr,maxY,maxX);

    makeMainMenu(maxX, maxY);

    while(strcmp(masterPassword, passwordCheck) != 0)
    {
        clearTextLine((((maxY/3)*2) + 2),0);
        mvprintw((((maxY/3)*2) + 2) , 0, "%s", "enter master password: ");
        getstr(passwordCheck);



        if (masterPassword[strlen(masterPassword) - 1] == '\n')
        {
            masterPassword[strlen(masterPassword) - 1] = '\0';
        } 
        else
        {
            masterPassword[strlen(masterPassword)] = '\0';
        }


        if(strcmp(masterPassword, passwordCheck) != 0)
        {
            passCount--;
            if(passCount > 0)
            {
                mvprintw((((maxY/3)*2) + 16) , 0, "invalid password. %d tries remaining.", passCount);
            }
            else
            {
                mvprintw((((maxY/3)*2) + 15) , 0, "max limit of tries reached. exiting program now...");
                destroyTable(hashTable);
                endwin();
            }
        }
        else
        {
            clearTextLine((((maxY/3)*2) + 2),0);
            clearTextLine((((maxY/3)*2) + 16),0);
            noecho();
            break;
        }

        memset(passwordCheck, 0, 256);
    }



    for(int i = 1; i < 6; i++)
    {
        makeMainMenuOptions(maxX, maxY, i, menuOptions[i - 1]);

    }

    mvprintw((maxY/8),5,character);
    move((maxY/8),5);


    c = getch();


    while (c != 'q')
    {

        if(c == 'w') 
        {
            getPos(&y,&x);
            if(y > 1) 
            {
                if((y - (maxY/8)) > 1)
                {

                    printw(" "); 
                    mvprintw((y - (maxY/8)), (x),character);
                    move(y - (maxY/8) , x);
                }
            }

        }
        else if(c == 's')
        {
            getPos(&y,&x);
            if(y < (maxY - (maxY/8)))
            {
                if((y + (maxY/8)) < ((maxY/3) * 2))
                {
                    printw(" ");
                    mvprintw((y+(maxY/8)), x,character);
                    move((y + (maxY/8)), x);
                }
            }
        }
        else if(c == '\n')
        {

            getPos(&y, &x);

            prevY = y;
            prevX = x;
            for(int i = 1; i < 7; i++)
            {
                tempMenuNumb[i] = (maxY/8) * i;
            }

            for(int i = 0; i < maxX; i++)
            {
                mvaddch(((maxY/3)*2) + 3, i, ' ');
            }

            if(y == tempMenuNumb[1])
            {
                echo();
                clearTextLine((((maxY/3)*2) + 2),0);
                memset(tempPass, 0, 256);
                memset(tempKey, 0, 256);
                clearMainMenu(maxX, maxY);
                mvprintw((((maxY/3)*2) + 2) , 0, "%s", "what program/site is this for? : ");
                getstr(tempKey);
                if(lookupData(hashTable, tempKey) == NULL)
                {
                    clearTextLine((((maxY/3)*2) + 2),0);
                    mvprintw((((maxY/3)*2) + 2) , 0, "%s", "enter new password into vault : ");
                    getstr(tempPass);
                    insertData(hashTable, tempKey, tempPass);
                    clearTextLine((((maxY/3)*2) + 2),0);
                    mvprintw((((maxY/3)*2) + 2) , 0, "%s", "new password successfully entered.");
                    passwordVaultSize++;
                }
                else
                {
                    clearTextLine((((maxY/3)*2) + 2),0);
                    mvprintw((((maxY/3)*2) + 2) , 0, "You already have a password entered for %s, try removing it or updating it instead.", tempKey);
                }
            }
            else if(y == tempMenuNumb[2])
            {
                echo();
                memset(tempPass, 0, 256);
                memset(tempKey, 0, 256);
                clearTextLine((((maxY/3)*2) + 2),0);
                mvprintw((((maxY/3)*2) + 2) , 0, "%s","what is the site/program you want to delete your info for? : ");
                getstr(tempKey);
                if(lookupData(hashTable, tempKey) != NULL)
                {
                    clearTextLine((((maxY/3)*2) + 2),0);
                    removeData(hashTable, tempKey);
                    mvprintw((((maxY/3)*2) + 2) , 0, "password successfully entered deleted.");
                    passwordVaultSize--;

                }
                else
                {
                    clearTextLine((((maxY/3)*2) + 2),0);
                    mvprintw((((maxY/3)*2) + 2) , 0, "%s","you don't seem to have any accounts for that site/program...");
                }
            }
            else if (y == tempMenuNumb[3])
            {
                echo();
                memset(tempStr, 0, 256);
                clearTextLine((((maxY/3)*2) + 2),0);
                mvprintw((((maxY/3)*2) + 2) , 0, "%s","what program/website is this password for? : ");
                getstr(tempStr);

                if(lookupData(hashTable, tempStr) != NULL)
                {
                    clearTextLine((((maxY/3)*2) + 2),0);
                    mvprintw((((maxY/3)*2) + 2) , 0,"Found it!\nYour %s Password is %s", tempStr,(char*)lookupData(hashTable, tempStr));
                }
                else
                {
                    clearTextLine((((maxY/3)*2) + 2),0);
                    mvprintw((((maxY/3)*2) + 2) , 0,"\nSorry, but I couldn't find any password for your %s account...\n\n", tempStr);
                }
            }
            else if(y == tempMenuNumb[4])
            {
                echo();
                memset(tempPass, 0, 256);
                memset(tempKey, 0, 256);
                clearTextLine((((maxY/3)*2) + 2),0);
                if(passwordVaultSize > 0)
                {
                    mvprintw((((maxY/3)*2) + 2) , 0,"what program/site account info do you want to to update? : ");
                    getstr(tempKey);

                    if(lookupData(hashTable, tempKey) != NULL)
                    {
                        clearTextLine((((maxY/3)*2) + 2),0);
                        mvprintw((((maxY/3)*2) + 2) , 0,"enter updated password into vault: ");
                        getstr(tempPass);
                        insertData(hashTable, tempKey, tempPass);
                        clearTextLine((((maxY/3)*2) + 2),0);
                        mvprintw((((maxY/3)*2) + 2) , 0,"enter updated password into vault: ");

                    }
                    else
                    {
                        clearTextLine((((maxY/3)*2) + 2),0);
                        mvprintw((((maxY/3)*2) + 2) , 0,"\n\nYou haven't entered a password for %s yet, try adding one instead\n\n", tempKey);
                    }
                }
                else
                {
                    clearTextLine((((maxY/3)*2) + 2),0);
                    mvprintw((((maxY/3)*2) + 2) , 0,"\n\nYou haven't entered any accounts to the vault, try doing that first..."); 
                }
            }
            else if(y == tempMenuNumb[5])
            {

                fp = fopen(fileName, "w");

                for(int i = 0; i < hashTable->size; i++)
                {

                    Node * temp = hashTable->table[i];

                    while(temp != NULL)
                    {
                        strcpy(outputData, (char *)temp->key);
                        strcat(outputData, ",");
                        strcat(outputData, (char *)temp->data);
                        fprintf(fp, "%s\n", outputData);
                        temp = temp->next;

                    }
                }

                fclose(fp);

                destroyTable(hashTable);
                endwin();
                break;
            }


            noecho();
            mvprintw(prevY, prevX,character);
            move(prevY, prevX);

        }
        else if(c == 'r')
        {

            for(int i = 4; i <= ((maxY/3)*2); i++)
            {
                for(int k = 3; k <= (maxX - 4 ); k++)
                {
                    mvaddch(i - 2, k  , ' ');
                }
            }
            // for(int i = 0; i <= ((maxX - 1)); i++)
            // {
            //     mvaddch(0,i,'1');
            //     mvaddch(((maxY/3)*2),i,'2');
            //     if(i > 1)
            //     {
            //         mvaddch(1, i , '3');
            //         mvaddch((((maxY/3)*2) - 1), i - 1, '4');
            //     }
            // }

            // for(int i = 0; i <= ((maxY/3)*2); i++)
            // {
            //     mvaddch(i,0,'5');
            //     mvaddch(i,(maxX - 1),'6');
            //     if(i > 1)
            //     {
            //         mvaddch(i - 1, 1, '7');
            //         mvaddch(i - 1, (maxX - 2), '8');
            //         mvaddch(i - 1, 2,'9');
            //         mvaddch(i - 1, (maxX - 3),'4');
            //     }

            // }
        }

        refresh();
        c = getch();
    }
    endwin();

    return 0;
}
