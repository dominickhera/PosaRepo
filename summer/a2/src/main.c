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
    int i;
    int prevX;
    int prevY;
    int passwordVaultSize = 0;
    // char fileName[256];
    char line[256];
    char tempPass[256];
    char tempKey[256];
    char tempStr[256];
    char * parse;
    FILE *fp;
    char tempString[10];


    y = 0;
    x = 0;


    char * menuOptions[] = {"Open Password File", "Add New Password", "Remove Password", "Retrieve a Password", "Update a Password", "Exit"}; 
    int tempMenuNumb[7];

    HTable * hashTable = createTable(5000, &hashData, &free, &printData);

    initscr();
    noecho();
    getmaxyx(stdscr,maxY,maxX);

    makeMainMenu(maxX, maxY);

    for(i = 1; i < 7; i++)
    {
        makeMainMenuOptions(maxX, maxY, i, menuOptions[i - 1]);

    }

    mvprintw((maxY/10),5,character);
    move((maxY/10),5);


    c = getch();


    while (c != 'q')
    {
        /*printw("%d",c);*/
        if(c == 'w') /*Wanting to move upwards*/
        {
            getPos(&y,&x);
            if(y > 1) /* than we can move up because were not at the top of the screen */
            {
                if((y - (maxY/10)) > 1)
                {
                    // printf("butts");

                    printw(" "); /*remove what the cursor is curently ontop of should be '@'*/
                    mvprintw((y - (maxY/10)), (x),character); /*Print the character in the new position */
                    move(y - (maxY/10) , x); /*re place the cursor into the correct position */
                }
            }

            // printw("Y : %d , X : %d, Max Y : %d, Max X : %d \n",y,x,maxY,maxX);
        }
        else if(c == 's') /*Wanting to move down*/
        {
            getPos(&y,&x);
            if(y < (maxY - (maxY/10)))
            {
                if((y + (maxY/10)) < ((maxY/3) * 2))
                {
                    printw(" ");
                    mvprintw((y+(maxY/10)), x,character);
                    move((y + (maxY/10)), x);
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
                tempMenuNumb[i] = (maxY/10) * i;
                // printf("tempNum%d: %d\n", i, tempMenuNumb[i]);
            }
            for(int i = 0; i < maxX; i++)
            {
                mvaddch(((maxY/3)*2) + 3, i, ' ');
            }


            if(y == tempMenuNumb[1])
            {
                clearTextLine((((maxY/3)*2) + 2),0);
                // for(int i = 0; i < maxX; i++)
                    // {
                    // mvaddch(((maxY/3)*2) + 3, i, ' ');
                    //         mvaddch(((maxY/3)*2) + 2, i, ' ');
                    // }
                    echo();
                mvprintw((((maxY/3)*2) + 2) , 0, "%s", "enter file name: ");
                getstr(tempString);
                // printf("entered %s", tempString);
                // scanf("%s", tempString);
                fp = fopen(tempString, "rw");
                if(fp == NULL)
                {
                    printf("could not find file\n\n");

                }
                else
                {
                    // printf("entered %s", tempString);


                    while(fgets(line, sizeof(line), fp) != NULL)
                    {
                        // printf("%s\n", line);
                        if(line[strlen(line) - 1] == '\n')
                        {
                            line[strlen(line) - 1] = '\0';
                        }

                        parse = strtok(line, ",");
                        // tempStore = parse;
                        strcpy(tempKey, parse);
                        // printf("website: %s ", parse);
                        while((parse = strtok(NULL, ",")) != NULL)
                        {
                            // tempStore = parse;
                            strcpy(tempPass, parse);
                            // printf("key: %s, data: %s\n", tempStore, parse);
                            // printf("password: %s\n", tempStore);

                        }
                        insertData(hashTable, tempKey, tempPass);
                        passwordVaultSize++;

                        // printf("key: %s, data: %s\n", tempKey, tempPass);

                    }
                }

                // clearTextLine((((maxY/3)*2) + 2),0);
                noecho();

            }
            else if(y == tempMenuNumb[2])
            {
                echo();
                clearTextLine((((maxY/3)*2) + 2),0);
                // printf("2");
                memset(tempPass, 0, 256);
                memset(tempKey, 0, 256);
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
                    // passwordVaultSize++;
                }
                else
                {
                    clearTextLine((((maxY/3)*2) + 2),0);
                    mvprintw((((maxY/3)*2) + 2) , 0, "%s", "You already have a password entered for that site, try removing it or updating it instead.", tempKey);
                }
            }
            else if(y == tempMenuNumb[3])
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
                    mvprintw((((maxY/3)*2) + 2) , 0, "%s", "password successfully entered deleted.");

                }
                else
                {
                    clearTextLine((((maxY/3)*2) + 2),0);
                    mvprintw((((maxY/3)*2) + 2) , 0, "%s","you don't seem to have any accounts for that site/program...");
                }
            }
            else if (y == tempMenuNumb[4])
            {
                echo();
                memset(tempStr, 0, 256);
                clearTextLine((((maxY/3)*2) + 2),0);
                mvprintw((((maxY/3)*2) + 2) , 0, "%s","what program/website is this password for? : ");
                getstr(tempStr);
                //             scanf("%s", tempStr);

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
            else if(y == tempMenuNumb[5])
            {
                echo();
                memset(tempPass, 0, 256);
                memset(tempKey, 0, 256);
                clearTextLine((((maxY/3)*2) + 2),0);
                mvprintw((((maxY/3)*2) + 2) , 0,"what program/site account info do you want to to update? : ");
                getstr(tempKey);

                if(lookupData(hashTable, tempKey) != NULL)
                {
                    clearTextLine((((maxY/3)*2) + 2),0);
                    mvprintw((((maxY/3)*2) + 2) , 0,"enter updated password into vault: ");
                    getstr(tempPass);
                    insertData(hashTable, tempKey, tempPass);

                }
                else
                {
                    clearTextLine((((maxY/3)*2) + 2),0);
                    mvprintw((((maxY/3)*2) + 2) , 0,"\n\nYou haven't entered a password for %s yet, try adding one instead\n\n", tempKey);
                }
            }
            else if(y == tempMenuNumb[6])
            {
                // printf("6");
                endwin();
                break;
            }
            // clearTextLine((((maxY/3)*2) + 2),0);
            noecho();
            mvprintw(prevY, prevX,character);
            move(prevY, prevX);



        }

        refresh();
        c = getch();
    }
    endwin();

    //         case 6:
    //             printList(hashTable);
    //             // printf("print list\n");
    //             // for(int i = 0; i < hashTable->size;i++)
    //             // {
    //             //     printf("key[%d], data[%s]\n", i, (char*)lookupData(hashTable, "facebook"));
    //             // }
    //             break;
    //         case 7:
    //             destroyTable(hashTable);
    //             return 0;
    //         default:
    //             printf("please enter a number between 1-7\n");
    //     }
    // }

    return 0;
}

